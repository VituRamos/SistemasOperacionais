import csv

def ler_arquivo(nome_arquivo):
    processos = []
    tempos_cpu = []
    tempos_chegada = []

    with open(nome_arquivo, 'r', newline='') as arquivo_csv:
        leitor_csv = csv.reader(arquivo_csv, delimiter=';')
        for linha in leitor_csv:
            if linha[0] == "Processo":
                processos = [str(elemento.strip()) for elemento in linha[1:]]
            elif linha[0] == "Tempo":
                tempos_cpu = [int(tempo.strip()) for tempo in linha[1:]]
            elif linha[0] == "Chegada":
                tempos_chegada = [int(tempo.strip()) for tempo in linha[1:]]

    return processos, tempos_cpu, tempos_chegada

def sjf_preemptivo(processos, tempos_cpu, tempos_chegada):
    tempo_atual = 0
    linha_tempo = []
    processos_restantes = list(range(len(processos)))

    while processos_restantes:
        processos_disponiveis = [i for i in processos_restantes if tempos_chegada[i] <= tempo_atual]

        if not processos_disponiveis:
            tempo_atual += 1
            linha_tempo.append("_")
        else:
            processos_na_fila = [(processos[i], tempos_cpu[i]) for i in processos_disponiveis]
            processos_na_fila.sort(key=lambda x: x[1])
            processo_atual, tempo_restante = processos_na_fila[0]

            for t in range(tempo_restante):
                tempo_atual += 1
                linha_tempo.append(processo_atual)

            processo_idx = processos.index(processo_atual)
            processos_restantes.remove(processo_idx)

    return linha_tempo

def formatar_linha_tempo(linha_tempo):
    linha_formatada = "|0|"
    tempo = 0
    processo_atual = None

    for processo in linha_tempo:
        if processo == processo_atual:
            tempo += 1
        else:
            if processo_atual:
                linha_formatada += f"------{processo_atual}-----−|{tempo}|"
            processo_atual = processo
            tempo += 1

    if processo_atual:
        linha_formatada += f"------{processo_atual}-----−|{tempo}|"

    return linha_formatada

def calcular_tempos_medios(tempos_espera, tempos_resposta, num_processos):
    tempo_medio_espera = sum(tempos_espera) / num_processos
    tempo_medio_resposta = sum(tempos_resposta) / num_processos
    return tempo_medio_espera, tempo_medio_resposta

# Nome do arquivo com os dados
nome_arquivo = "Teste.csv"  

# Leitura dos dados do arquivo
processos, tempos_cpu, tempos_chegada = ler_arquivo(nome_arquivo)

# Executar o escalonador SJF preemptivo
linha_tempo_sjf = sjf_preemptivo(processos, tempos_cpu, tempos_chegada)

# Calcular tempos médios de espera e resposta
num_processos = len(processos)
tempos_espera = [linha_tempo_sjf.index(processo) for processo in processos]
tempos_resposta = [tempos_espera[i] - tempos_chegada[i] for i in range(num_processos)]

linha_tempo_formatada = formatar_linha_tempo(linha_tempo_sjf)

# Exibir relatório
print("Processos na Fila do SJF Preemptivo:")
print("   " + "    ".join(processos))
print("\nTempo de CPU requerida pelos processos:")
print("   " + "    ".join(map(str, tempos_cpu)))
print("\nTempo de Chegada dos processos:")
print("   " + "    ".join(map(str, tempos_chegada)))
print("\nLinha do Tempo:")
print((linha_tempo_formatada))
print("\nTempos Médios:")
tempo_medio_espera, tempo_medio_resposta = calcular_tempos_medios(tempos_espera, tempos_resposta, num_processos)
print(f"Tempo Médio de Espera: {tempo_medio_espera}")
print(f"Tempo Médio de Resposta: {tempo_medio_resposta}")