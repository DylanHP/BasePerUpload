import serial
import serial.tools.list_ports
import time
import csv
import os
from datetime import datetime

# Setup
OUTPUT_FILE = 'sensor_data.csv'
BAUD_RATE = 115200

# Verifica se il file esiste
file_exists = os.path.isfile(OUTPUT_FILE)

# Funzione per trovare la porta seriale di Arduino
def find_arduino_port():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        # Controlla se il nome del dispositivo contiene "Arduino"
        if 'Arduino' in port.description or 'USB' in port.description:
            return port.device
    return None

# Trova la porta di Arduino
COM_PORT = find_arduino_port()
if COM_PORT is None:
    print("Arduino non trovato. Assicurati che sia collegato.")
    exit()

# Inizializza la connessione seriale
ser = serial.Serial(COM_PORT, BAUD_RATE)
time.sleep(2)  # Attendi che la connessione si stabilisca

# Apri il file CSV in modalità scrittura
with open(OUTPUT_FILE, mode='a', newline='', encoding='utf-8') as csv_file:
    csv_writer = csv.writer(csv_file)

    # Scrivi l'intestazione del file CSV solo se il file è stato appena creato
    if not file_exists:
        csv_writer.writerow(['Temperatura Esterna[°C]', 'Temperatura Espulsione[°C]', 'Temperatura Interna[°C]', 'Temperatura Immissione[°C]', 'Temperatura Condensatore[°C]', 'Temperatura Evaporatore[°C]', 'Temperatura di Dew Point[°C]', 'Temperatura di bulbo umido[°C]', 'Tempo[H:M:S]', 'Data[D-M-Y]'])

    try:
        while True:
            # Leggi il flusso dei dati dalla seriale e scrivilo nel file
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()  # Leggi la linea dalla seriale

                # aggiungo l'ora e data attuale
                line += "," + datetime.now().strftime("%H:%M:%S,%d-%m-%Y")
                print(line)  # Stampa la linea nel terminale

                # Dividi la linea in valori separati da virgola
                data = line.split(',')

                # Verifica che ci siano esattamente 7 valori
                if len(data) == 10:
                    temperaturaEsterna       = data[0]
                    temperaturaEspulsione    = data[1]
                    temperaturaInterna       = data[2]
                    temperaturaImmissione    = data[3]
                    temperaturaCondensatore  = data[4]
                    temperaturaEvaporatore   = data[5]
                    temperaturaDewPoint      = data[6]
                    temperaturaBulboUmido    = data[7]
                    tempo                    = data[8]
                    date                     = data[9]

                    # Scrivi i valori nel file CSV
                    csv_writer.writerow([
                        temperaturaEsterna, 
                        temperaturaEspulsione, 
                        temperaturaInterna, 
                        temperaturaImmissione, 
                        temperaturaCondensatore, 
                        temperaturaEvaporatore, 
                        temperaturaDewPoint, 
                        temperaturaBulboUmido, 
                        tempo, 
                        date
                    ])

            time.sleep(0.1)  # Aggiungi un breve ritardo per evitare di sovraccaricare la CPU

    except KeyboardInterrupt:
        print("Interruzione del programma.")

    finally:
        # Chiudi la connessione seriale
        ser.close()