# código muito simplificado para criar um banco de dados de exemplo.
import sqlite3
import os


def main():
    # abre uma conexão
    database_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), '../servidor/banco.db')

    if os.path.exists(database_path):
        os.remove(database_path)

    # abre uma conexão com o banco e fecha automaticamente no fim do bloco with
    with sqlite3.connect(database_path) as con:
        # pega um cursor, que é o objeto que irá executar as transações
        # pega um cursor, que é o objeto que irá executar as transações
        cur = con.cursor()

        cur.execute('''
            CREATE TABLE IF NOT EXISTS sinais (
            sinal_id int primary key,
            sinal float
            )
               ''')
        # salva modificações
        con.commit()

if __name__ == '__main__':
    main()