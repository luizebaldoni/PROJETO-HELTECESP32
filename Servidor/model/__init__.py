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

def select_rows(cursor: sqlite3.Cursor, clause: str) -> list:
    #faz seleção das tuplas de uma tabela - qualquer comando sqlite
    #cursor = para o banco de dados
    #clause = faz a seleçao (SELECT * FROM table)

    res = cursor.execute(clause)
    rows = []
    for row in res:
        rows += [tuple([row[k] for k in row.keys()])]

    return rows

def raw_execute(cursor: sqlite3.Cursor, clause: str) -> sqlite3.Cursor:
    #executa o comando sqlite e retorna o resultado
    #cursor = para o banco de dados
    #clause = clausula sqlite
    #return = retorno da execuçao da clausula

    return cursor.execute(clause)

def remove_db(file: str) -> None:
    #deleta o arquivo .db 
    #file caminho para o banco de dados

    try:
        os.remove(file)
    except FileNotFoundError:
        pass

def main(path: str = '.', db_name: str = 'test.db') -> None:
    remove_db(os.path.join(path, db_name))

    with SQLite(os.path.join(path, db_name)) as cursor:
        create_table(
            cursor,
            """"
            'nome da tabela',
            {nome da coluna: dado}
            """"
        )

        insert_rows(
            cursor, 
            """
            'nome da tabela'
            [
                {chave: ., nome da coluna: item}
            ]
            """
        )

if __name__ == '__main__':
    main()