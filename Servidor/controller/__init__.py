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

def get_table_column_names(cursor: sqlite3.Cursor, table_name: str) -> list:
    #pega o nome das colunas do banco de dados
    # cursor = para o banco de dados
    # table_name = nome da tabela
    # return =  o nome das tabelas do banco como lista

    res = model.raw_execute(cursor, 'PRAGMA table_info(%s)' % table_name)
    column_names = [x[1] for x res.fetchall()]
    return column_names

def main()
    app = Flask(__name__) #inicia o flask
    db_path = os.path.join(filepath, '..', 'model')
    db_name = 'test.db'
    #deleta e cria o banco toda vez q o backend for iniciado
    model.main(db_path, db_name)

    @app.route('/')
    def initial_page()

        return '''
        <p> arquivo html com a pagina inicial</p>
        '''

    @app.route('/populate_table', methods = ['POST'])
    def populate_table()
        with model.SQLite(os.path.join(db_path, db_name)) as cursor:
            lista_de_tuplas = model.select_rows(cursor, "SELECT * FROM #nome da tabela")

            colunas = get_table_column_names(cursor, 'filme')
            #lista que vai conter dicionarios criados
            lista_de_dicionarios = []

            #unir as listas e converter em dicionario
            for i in range(len(lista_de_tuplas)):
                dicionario = {}
                for j in range(len(colunas)):
                    dicionario[colunas[j]] = lista_de_tuplas[i][j]
                
                #adiciona os dicts na lista
                lista_de_dicionarios.append(dicionarios)
            
            response = jsonify(lista_de_dicionarios)

            #adicionar esta linha para as respostas 
            response.headers.add('Access-Control-Allow-Origin', '*')
            return response

@app.route('/selcte_and_populate_table', methods = ['POST'])
def select_and_populate_table():
    with model, SQLite(os.path,join(db_path, db_name)) as cursor:
        chamada = request.form['second_task_table_selector']
        colunas = get_table_column_names(cursor, chamada)
        select = 'SELECT * FROM ' + chamada

        lista_de_tuplas = model.select_rows(cursor, select)

        #lista vazia que vai conter os dicts
        lista_de_dicionarios = []

        #une listas e cria diconarios
        for i in range(len(lista_de_tuplas)):
            dicionario = {}
            for j in range(len(colunas)):
                dicionario[colunas[j]] = lista_de_tuplas[i][j]

            #adiciona os dicionarios na lista
            lista_de_dicionarios.append(dicionario)
        
        response = jsonify(lista_de_dicionarios)

        response.headers.add('Access-Control-Allow-Origin', '*')
        return response

    #coloca o backend rodar
    app.run()

if __name__ == '__main__':
    main()

