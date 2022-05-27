import os
import sqlite3
from flask import Flask, request, jsonify, render_template
import sys

filepath = os.path.dirname(__file__)
sys.path.append(os.path.join(filepath, '..'))

import model


def get_table_column_names(cursor: sqlite3.Cursor, table_name: str) -> list:
    res = model.raw_execute(cursor, 'PRAGMA table_info(%s)' % table_name)
    column_names = [x[1] for x in res.fetchall()]
    return column_names


def main():
    app = Flask(__name__)  # inicia uma aplicação do flask (o backend)
    db_path = os.path.join(filepath, '..', 'model')
    db_name = 'test.db'
    # deleta & cria o banco de dados, toda vez que o backend for iniciado
    model.main(db_path, db_name)

    #colocando o yours.html como pagina inicial
    app = Flask(__name__, template_folder=os.path.join(filepath, '..', 'view', 'pages'))
    @app.route('/')
    def initial_page():
        return render_template('main.html')

    #populando tabela:
    @app.route('/populate_table', methods=['POST'])
    def populate_table():
     with model.SQLite(os.path.join(db_path, db_name)) as cursor:
        nome_tabela ='SINAIS' #selecionando tabela para aparecer
        busca = 'SELECT id_sinais, data_sinais, sinal_sensor FROM %s' % nome_tabela #indicando colunas para puxar
        tabela = model.select_rows(cursor, busca)
        dicionarios = [] #convertendo em dicionarios

        for linha in tabela:
            dicionarios.append({'id_sinais': linha[0], 'data_sinais': linha [1], 'sinal_sensor': linha[2]
                })
        response = jsonify(dicionarios) #mandando retornar os dicionarios
        response.headers.add('Access-Control-Allow-Origin', '*')
        return response

    @app.route('/select_and_populate_table', methods=['POST'])
    def select_and_populate_table():
        with model.SQLite(os.path.join(db_path, db_name)) as cursor:

            nome_tabela = request.form['second_task_table_selector'] # puxando a tabela
            busca = 'SELECT * FROM %s' % nome_tabela #selecionando oq buscar das tabelas
            tabela = model.select_rows(cursor, busca)

            #convertendo em dicionarios
            dicionarios = []
            for linha in tabela:
                dicionarios.append({
                        'id_sinais': linha[0],
                        'data_sinais': linha [1],
                        'sinal_sensor': [2]
                        })

            response = jsonify(dicionarios) #mandando retornar os dicionarios
            response.headers.add('Access-Control-Allow-Origin', '*')
            return response

    # coloca o backend a rodar
    app.run(debug=True) #fazendo o servidor reiniciar automaticamente dps de modificações


if __name__ == '__main__':
    main()
