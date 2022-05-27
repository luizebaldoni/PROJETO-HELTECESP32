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

def nomecoluna(cursor: sqlite3.Cursor, tabnome: str) -> list:
    #pega o nome das colunas do banco de dados
    # cursor = para o banco de dados
    # table_name = nome da tabela
    # return =  o nome das tabelas do banco como lista

    res = model.raw_execute(cursor, 'PRAGMA table_info(%s)' % tabnome)
    colnome = [x[1] for x in res.fetchall()]
    return colnome

def main():
    app = Flask(__name__) #inicia o flask
    db_path = os.path.join(filepath, '..', 'model')
    dbnome = 'test.db'
    #deleta e cria o banco toda vez q o backend for iniciado
    model.main(db_path, dbnome)


    @app.route('/populate_table', metodos = ['POST'])
    def populate_table():
        with model.SQLite(os.path.join(db_path, dbnome)) as cursor:
            ltuplas = model.select_rows(cursor, "SELECT * FROM #nome da tabela")

            colunas = nomecoluna(cursor, '*nome da coluna')
            #lista que vai conter dicionarios criados
            ldict = []

            #unir as listas e converter em dicionario
            for i in range(len(ltuplas)):
                dicionario = {}
                for j in range(len(colunas)):
                    dicionario[colunas[j]] = ltuplas[i][j]
                
                #adiciona os dicts na lista
                ldict.append(dicionario)
            
            response = jsonify(ldict)

            #adicionar esta linha para as respostas 
            response.headers.add('Access-Control-Allow-Origin', '*')
            return response

@app.route('/selcte_and_populate_table', methods = ['POST'])
def preenchertabela():
    with model, SQLite(os.path,join(db_path, dbnome)) as cursor:
        chamada = request.form['second_task_table_selector']
        colunas = nomecoluna(cursor, chamada)
        select = 'SELECT * FROM ' + chamada

        ltuplas = model.select_rows(cursor, select)

        #lista vazia que vai conter os dicts
        ldict = []

        #une listas e cria diconarios
        for i in range(len(ltuplas)):
            dicionario = {}
            for j in range(len(colunas)):
                dicionario[colunas[j]] = ltuplas[i][j]

            #adiciona os dicionarios na lista
            ldict.append(dicionario)
        
        response = jsonify(ldict)

        for linha in tabela:
            dicionarios.append({'id_sinais': linha[0], 'data_sinais': linha [1], 'sinal_sensor': [2]
                })
        response = jsonify(dicionarios) #mandando retornar os dicionarios
        response.headers.add('Access-Control-Allow-Origin', '*')
        return response
    app.run()
if __name__ == '__main__':
    main()