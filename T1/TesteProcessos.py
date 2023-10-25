import openpyxl
import csv

#Ler arquivo .csv
def ler_arquivo_csv(nome_arquivo):
    processos = []
    tempos_cpu = []
    tempos_chegada = []

    with open(nome_arquivo, 'r', newline='') as arquivo_csv:
        
        leitor_csv = csv.reader(arquivo_csv, delimiter=';')
        
        for linha in leitor_csv:
            
            #A partir do segundo elemento da linha "Processo" transformar em string e strip
            if linha[0] == "Processo":
                processos = [str(elemento.strip()) for elemento in linha[1:]] 
                
            #A partir do segundo elemento da linha "Tempo" transformar em int e strip
            elif linha[0] == "Tempo":
                tempos_cpu = [int(tempo.strip()) for tempo in linha[1:]] 
                
            #A partir do segundo elemento da linha "Chegada" transformar em int e strip
            elif linha[0] == "Chegada":
                tempos_chegada = [int(tempo.strip()) for tempo in linha[1:]]  

    return processos, tempos_cpu, tempos_chegada


#ler arquivo .xlsx
def ler_arquivo_xlsx(nome_arquivo):
    processos = []
    tempos_cpu = []
    tempos_chegada = []
    
    #Abrir arquivo .xlsx
    workbook = openpyxl.load_workbook(nome_arquivo)
    
    #Abrir planilha ativa
    worksheet = workbook.active

    for linha in worksheet.iter_rows(values_only=True):
        
        if linha[0] == "Processo":
            processos = [str(elemento) for elemento in linha[1:]]
        
        elif linha[0] == "Tempo":
            tempos_cpu = [int(tempo) for tempo in linha[1:]]
        
        elif linha[0] == "Chegada":
            tempos_chegada = [int(tempo) for tempo in linha[1:]]

    return processos, tempos_cpu, tempos_chegada


#Funcao SJF 
def sjf_preemptivo(processos, tempos_modificados_cpu, tempos_modificados_chegada):
    
    tempo_atual = 0 
    linha_tempo = [] 
    
    #Lista indices dos processos restantes
    processos_restantes = list(range(len(processos))) 

    #Enquanto houverem processos restantes
    while processos_restantes:
        
        #Lista indices de processos com tempo de chegada <= tempo atual
        processos_disponiveis = [i for i in processos_restantes if tempos_modificados_chegada[i] <= tempo_atual]

        #Insere processo na fila
        processos_na_fila = [(processos[i], tempos_modificados_cpu[i]) for i in processos_disponiveis]
            
        #Ordena os processos (Menor tempo de CPU)
        processos_na_fila.sort(key=lambda x: x[1])
            
        #Recebe info do processo
        processo_atual, tempo_restante = processos_na_fila[0]

        #Processo é adicionado a linha do tempo com base em seu tempo de cpu
        tempo_atual += 1
        linha_tempo.append(processo_atual)
            
        #Decrementar tempos do processo atual
        tempos_modificados_cpu[(processos.index(processo_atual))] -=1

        #Remove o processo da lista de procesos restantes caso tempo de cpu zere
        if tempos_modificados_cpu[(processos.index(processo_atual))] == 0:
            processos_restantes.remove(processos.index(processo_atual))

    return linha_tempo


#Formatar linha do tempo 
def formatar_linha_tempo(linha_tempo):
    linha_formatada = "|0|"
    tempo = 0
    processo_atual = None

    #Para cada processo em linha do tempo
    for processo in linha_tempo:
        
        #Se o processo se manter o mesmo
        if processo == processo_atual:
            tempo += 1
            
        #Se o processo mudar
        else:
            
            #Se existir processo_atual
            if processo_atual:
                
                #Adiciona nova parte da linha em linha formatada
                linha_formatada += f"------{processo_atual}-----−|{tempo}|"
            
            #Atualizacao do processo atual e tempo++ para inserir posteriormente na linha formatada
            processo_atual = processo
            tempo += 1

    #Se apos o loop ainda restar um processo
    if processo_atual:
        linha_formatada += f"------{processo_atual}-----−|{tempo}|"
        

    return linha_formatada


#Calcular tempo final para cada processo
def calcular_tempos_finais(linha_tempo):
    tempo = 0
    processo_atual = None
    linha_tempo_mod = []

    #Gerar linha do tempo_final (semelhante ao "Formatar linha tempo")
    for processo in linha_tempo:
        
        if processo == processo_atual:
            tempo += 1
            
        else:
            
            if processo_atual:
                
                linha_tempo_mod += [(processo_atual,tempo)]
            
            processo_atual = processo
            tempo += 1

    if processo_atual:
        linha_tempo_mod += [(processo_atual,tempo)]


    #Ordenar tempos em valores unicos para tupla = [(Tempo P1),(Tempo P2)...]
    processo_nome = {}

    #Para cada elemento em linha_tempo
    for elemento in linha_tempo_mod:
        string, valor = elemento
        
        #Se string ja estiver em processo_nome
        if string in processo_nome:
            
            #Recebe maior valor em que a string se repete
            processo_nome[string] = max(processo_nome[string], valor)
            
        #Se string nao estiver em processo_nome
        else:
            
            #Processo_nome recebe valor
            processo_nome[string] = valor

    #Recebe tempo de cada processo
    tempos = [(processo_nome[string]) for string in processo_nome]

    return tempos


def calcular_tempos_medios(tempos_espera, tempos_resposta, quantidade_processos):
    tempo_medio_espera = sum(tempos_espera) / quantidade_processos
    tempo_medio_resposta = sum(tempos_resposta) / quantidade_processos
    return tempo_medio_espera, tempo_medio_resposta


#Nome do arquivo
nome_arquivo = "Input.xlsx"  

#Leitura dos dados do arquivo
processos, tempos_cpu, tempos_chegada = ler_arquivo_xlsx(nome_arquivo)

#Tempos de leitura que serao modificados
tempos_modificados_cpu = [(tempos) for tempos in tempos_cpu]
tempos_modificados_chegada = [(tempos) for tempos in tempos_chegada]

#Executar SJF preemptivo
linha_tempo_sjf = sjf_preemptivo(processos, tempos_modificados_cpu, tempos_modificados_chegada)

#Calcular tempos medios
quantidade_processos = len(processos)
tempos_finais = calcular_tempos_finais(linha_tempo_sjf)
tempos_espera = [tempos_finais[i] - (tempos_chegada[i] + tempos_cpu[i]) for i in range(quantidade_processos)]
tempos_resposta = [tempos_finais[i] - tempos_chegada[i] for i in range(quantidade_processos)]
tempo_medio_espera, tempo_medio_resposta = calcular_tempos_medios(tempos_espera, tempos_resposta, quantidade_processos)

linha_tempo_formatada = formatar_linha_tempo(linha_tempo_sjf)

#Exibir resultados
print("Processos na Fila do SJF Preemptivo:")
print("    ".join(processos))

print("\nTempo de CPU requerida pelos processos:")
print("    ".join(map(str, tempos_cpu)))

print("\nTempo de Chegada dos processos:")
print("    ".join(map(str, tempos_chegada)))

print("\nLinha do Tempo:")
print((linha_tempo_formatada))

print("\nTempos Médios:")
print(f"Tempo Médio de Espera: {tempo_medio_espera}")
print(f"Tempo Médio de Resposta: {tempo_medio_resposta}")
