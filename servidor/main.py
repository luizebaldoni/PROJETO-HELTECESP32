import serial
import sqlite3
import os


def main():
    comunicacao = serial.Serial('COM3', 9600)
    print(serial)
    database_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), '../servidor/banco.db')
    with sqlite3.connect(database_path) as con:
        cur = con.cursor()  # cria cursor
        add_sinais = comunicacao.readline()
        try:
            ultimo_id = int(cur.execute('SELECT MAX(sinal_id) from sinais').fetchone()[0]) + 1
        except:
            ultimo_id = 0

        cur.execute(
            'INSERT INTO sinais(sinal_id, sinal_umidade) VALUES ({0}, \'{1}\')'.format(ultimo_id, add_sinais))

        con.commit()


if __name__ == '__main__':
    main()
