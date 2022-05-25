import os
import sqlite3
from flask import Flask, request, jsonify
import sys

filepath = os.path.dirname(__file__)
sys.path.append(os.path.join(filepath, "'.."))

# importa módulo do banco de dados; permite rodar as funções desse módulo através da sintaxe 
# model.<nome_da_função>
# por exemplo, model.select_rows
# para selecionar as linhas

import model 

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

    @app.route('/')
    def initial_page():

        return '''
        <p> arquivo html com a pagina inicial</p>
        '''

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

        response.headers.add('Access-Control-Allow-Origin', '*')
        return response

    #coloca o backend rodar
    app.run()

if __name__ == '__main__':
    main()

