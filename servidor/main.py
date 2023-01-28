import serial
import sqlite3
import os


def main():
    comunicacao = serial.Serial('COM3', 9600)
    print(serial)
    database_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), '../servidor/banco.db')
    with sqlite3.connect(database_path) as con:
        cur = con.cursor()  # cria cursor
        add_sinais = ('INSERT INTO sinais (sinal_id, sinal_umidade, sinal_temperatura) VALUES (%d, %s, %s )')
        while(True):
            serialValue = comunicacao.readline().split("|")
            cur.execute(serialValue)
            con.commit()


if __name__ == '__main__':
    main()
