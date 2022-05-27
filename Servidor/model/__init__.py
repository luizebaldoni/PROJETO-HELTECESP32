import os
import sqlite3

class SQLite( object ):
    def __init__(self, file):
        self.file = file

    def __enter__(self):
        self.conn = sqlite3.connect( self.file )
        self.conn.row_factory = sqlite3.Row
        return self.conn.cursor()

    def __exit__(self, type, value, traceback):
        self.conn.commit()
        self.conn.close()

def create_table(cursor: sqlite3.Cursor, table: str, fields: dict, other_data: list = None) -> None:

    command = "CREATE TABLE %s (%s)" % (
        table,
        ','.join( [k + ' ' + v for k, v in fields.items()] + (
            other_data if other_data is not None else []) )
    )
    cursor.execute( command )

def insert_rows(cursor: sqlite3.Cursor, table: str, tuples: list) -> None:

    for some_tuple in tuples:
        tuple_values = []
        for v in some_tuple.values():
            if isinstance( v, str ):
                tuple_values += ['\'' + v + '\'']
            else:
                tuple_values += [str( v )]

        command = "INSERT INTO %s(%s) VALUES (%s)" % (
            table, ','.join( map( str, some_tuple.keys() ) ), ','.join( tuple_values )
        )
        cursor.execute( command )


def select_rows(cursor: sqlite3.Cursor, clause: str) -> list:

    res = cursor.execute( clause )
    rows = []
    for row in res:  # type: sqlite3.Row
        rows += [tuple( [row[k] for k in row.keys()] )]

    return rows


def raw_execute(cursor: sqlite3.Cursor, clause: str) -> sqlite3.Cursor:

    return cursor.execute( clause )


def remove_db(file: str) -> None:

    try:
        os.remove( file )
    except FileNotFoundError:
        pass


def main(path: str = '.', db_name: str = 'test.db') -> None:
    remove_db( os.path.join( path, db_name ) )

    with SQLite( os.path.join( path, db_name ) ) as cursor:
        # todas as tabelas possuem mais de 4 colunas
        # foram feitas mais de 4 tabelas
        create_table(
            cursor,
            'SINAIS',  # tabela com 10 tuplas (no caso acho que tem mais)
            {
                'id_sinais': ' INTEGER AUTOINCREMENT',
                'data_sinais': 'datetime NOT NULL DEFAULT CURRENT TIMESTAMP',
                'sinal_sensor':'float NOT NULL'})
      
if __name__ == '__main__':
    main()
