import os
import sqlite3
from flask import Flask, request, jsonify, render_template
import sys
import serial

filepath = os.path.dirname(__file__)
sys.path.append(os.path.join(filepath, '..'))

import model

def get_nome_colunas(cursor: sqlite3.Cursor, table_name: str) -> list:
    res = model.raw_execute(cursor, 'PRAGMA table_info(%s)' % table_name)
    column_names = [x[1] for x in res.fetchall()]
    return column_names


def main():
    app = Flask(__name__)  # inicia uma aplicação do flask (o backend)
    db_path = os.path.join(filepath, '..', 'model')
    db_name = 'test.db'
    # deleta & cria o banco de dados, toda vez que o backend for iniciado
    model.main(db_path, db_name)

 #populando tabela:
    @app.route('/itens_tabela', methods=['POST'])
    def populate_table():
     with model.SQLite(os.path.join(db_path, db_name)) as cursor:
        nome_tabela ='SINAIS' #selecionando tabela para aparecer
        busca = 'SELECT id_sinais, data_sinais, sinal_sensor FROM %s' % nome_tabela #indicando colunas para puxar
        tabela = model.select_rows(cursor, busca)
        dicionarios = [] #convertendo em dicionarios


        for linha in tabela:
            dicionarios.append({'id_sinais': linha[0], 'data_sinais': linha [1], 'sinal_sensor': [2]
                })
        response = jsonify(dicionarios) #mandando retornar os dicionarios
        response.headers.add('Access-Control-Allow-Origin', '*')
        return response
    app.run()
if __name__ == '__main__':
    main()