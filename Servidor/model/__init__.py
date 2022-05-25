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


def create_table(cursor: sqlite3.Cursor, tabela: str, dicionario: dict, chaveEst: list = None):
    # criar tabelas
    # cursor = para o banco de dados
    # tabela = nome da tabela
    # dicionario = dict onde a chave é o nome da coluna e o valor e tipo
    # chaveEst = define foreign keys ou outras config

    comando = "CREATE TABLE %s (%s)" % (
        tabela,
        ','.join([k + ' ' + v for k, v in dicionario.items()] + (
            chaveEst if chaveEst is not None else []))
    )
    cursor.execute(comando)

def insert_rows(cursor: sqlite3.Cursor, tabela: str, tuplas: list):
    #insere tuplas na tabela 
    #cursor = para o banco de dados
    #tabela = nome da tabela
    #tuples = lista de dicionarios

    for tupla in tuplas:
        vtuplas = []
        for v in tupla.values():
            if isinstance(v, str):
                tupla += ['\'' + v + '\'']
            else:
                tupla += [str(v)]

        command = "INSERT INTO %s(%s) VALUES (%s)" % (
            tabela, ','.join(map(str, tupla.keys())), ','.join(vtuplas)
        )
        cursor.execute(command)

def select_rows(cursor: sqlite3.Cursor, selecao: str) -> list:
    #faz seleção das tuplas de uma tabela - qualquer comando sqlite
    #cursor = para o banco de dados
    #selecao = faz a seleçao (SELECT * FROM table)

    res = cursor.execute(selecao)
    rows = []
    for row in res:
        rows += [tuple([row[k] for k in row.keys()])]

    return rows

def raw_execute(cursor: sqlite3.Cursor, clausula: str) -> sqlite3.Cursor:
    #executa o comando sqlite e retorna o resultado
    #cursor = para o banco de dados
    #clausula = clausula sqlite
    #return = retorno da execuçao da clausula

    return cursor.execute(clausula)

def remove_db(doc: str) -> None:
    #deleta o arquivo .db 
    #file caminho para o banco de dados

    try:
        os.remove(doc)
    except FileNotFoundError:
        pass

def main(path: str = '.', dbnome: str = 'test.db') -> None:
    remove_db(os.path.join(path, dbnome))

    with SQLite(os.path.join(path, dbnome)) as cursor:
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