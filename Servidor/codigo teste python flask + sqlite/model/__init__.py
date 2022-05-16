import os
import sqlite3

class SQLite(object):
    def __init__(self, file):
        self.file = file

    def __enter__(self):
        self.conn = sqlite3.connect(self.file)
        self.conn.row_factory = sqlite3.Row
        return self.conn.cursor()

    def __exit__(self, type, value, traceback):
        self.conn.commit()
        self.conn.close()


def create_table(cursor: sqlite3.Cursor, table: str, fields: dict, other_data: list = None):
    # criar tabelas
    # cursor = para o banco de dados
    # table = nome da tabela
    # fields = dict onde a chave é o nome da coluna e o valor e tipo
    # other_data = define foreign keys ou outras config

    command = "CREATE TABLE %s (%s)" % (
        table,
        ','.join([k + ' ' + v for k, v in fields.items()] + (
            other_data if other_data is not None else []))
    )
    cursor.execute(command)

def insert_rows(cursor: sqlite3.Cursor, table: str, tuples: list):
    #insere tuplas na tabela 
    #cursor = para o banco de dados
    #table = nome da tabela
    #tuples = lista de dicionarios

    for some_tuple in tuples:
        tuple_values = []
        for v in some_tuple.values():
            if isinstance(v, str):
                tuple_values += ['\'' + v + '\'']
            else:
                tuple_values += [str(v)]

        command = "INSERT INTO %s(%s) VALUES (%s)" % (
            table, ','.join(map(str, some_tuple.keys())), ','.join(tuple_values)
        )
        cursor.execute(command)