
#include <iostream>
#include <string>
#include <iomanip>
#include <queue>

struct paciente
{
    std::string senha;
    char prioridade;
    int hh;  
    int mm;
    int total_minutos;
};

struct atendimento
{
    int hh;
    int mm;
    int total_minutos;
};

int atendimentos = 0;

int pico_lotacao = 0;

int espera = 0;

int atendimentos_prioridadeV = 0;
int atendimentos_prioridadeA = 0;
int atendimentos_prioridadeD = 0;
int atendimentos_prioridadeB = 0;


std::queue<paciente> FilaV; // Fila de emergência
std::queue<paciente> FilaA; // Fila Urgente
std::queue<paciente> FilaD; // Fila Pouco Urgente
std::queue<paciente> FilaB; // Fila não urgente

void print_tempo(int h, int m) {
    std::cout << std::setfill('0') << std::setw(2) << h << ":"
              << std::setfill('0') << std::setw(2) << m;
}


void calcular_pico_lotacao(){
    int soma_filas = FilaV.size()+FilaA.size()+FilaD.size()+FilaB.size();
    if (soma_filas > pico_lotacao)
    {
        pico_lotacao = soma_filas;
    }  
}


int cadastrar_paciente(const paciente &dados){
    switch(dados.prioridade){
        case 'V':
            FilaV.push(dados);
            std::cout << "Paciente " << dados.senha << " cadastrado. Entrada: ";
            print_tempo(dados.hh, dados.mm);
            std::cout << std::endl;
            break;
        case 'A':
            FilaA.push(dados);
            std::cout << "Paciente " << dados.senha << " cadastrado. Entrada: ";
            print_tempo(dados.hh, dados.mm);
            std::cout << std::endl;
            break;
        case 'D':
            FilaD.push(dados);
            std::cout << "Paciente " << dados.senha << " cadastrado. Entrada: ";
            print_tempo(dados.hh, dados.mm);
            std::cout << std::endl;
            break;
        case 'B':
            FilaB.push(dados);
            std::cout << "Paciente " << dados.senha << " cadastrado. Entrada: ";
            print_tempo(dados.hh, dados.mm);
            std::cout << std::endl;
            break;
        default:
            std::cout << "Erro: Código de prioridade " << dados.prioridade << " inválido." << std::endl;
            return -1;
    }
    return 0;
}

int atender_paciente(const atendimento &tempo_atendimento, int &atendimentos){
    paciente atendido;
    bool encontrado = false;
    if (!FilaV.empty()) {
        atendido = FilaV.front();
        atendimentos_prioridadeV++;
        FilaV.pop();
        encontrado = true;
    } else if (!FilaA.empty()) {
        atendido = FilaA.front();
        atendimentos_prioridadeA++;
        FilaA.pop();
        encontrado = true;
    } else if (!FilaD.empty()) {
        atendido = FilaD.front();
        atendimentos_prioridadeD++;
        FilaD.pop();
        encontrado = true;
    } else if (!FilaB.empty()) {
        atendido = FilaB.front();
        atendimentos_prioridadeB++;
        FilaB.pop();
        encontrado = true;
    }

    if (encontrado) {
        int tempo_esperado = tempo_atendimento.total_minutos - atendido.total_minutos;
        if (tempo_esperado > espera)
        {
            espera = tempo_esperado;
        }
        
        std::cout << " Paciente " << atendido.senha << " (" << atendido.prioridade << ") atendido." << std::endl;
        std::cout << "   - Entrada: ";
        print_tempo(atendido.hh, atendido.mm);
        std::cout << std::endl;
        std::cout << "   - Atendimento: ";
        print_tempo(tempo_atendimento.hh, tempo_atendimento.mm);
        std::cout << std::endl;
        atendimentos++;
        return 0;   
    } else {
        std::cout << "Sem pacientes aguardando atendimento" << std::endl;
        return -1;
    }
}

void informacoes(){

    std::cout << " V : " << FilaV.size() << " , ";
    std::cout << " A : " << FilaA.size() << " , ";
    std::cout << " D : " << FilaD.size() << " , ";
    std::cout << " B : " << FilaB.size() << " , ";
    std::cout << " Total de pacientes atendidos " << atendimentos << std::endl;
}



int main(){

    char x;
    paciente dados;
    atendimento atendimento;
    
    std::cout << "Sistema de Triagem. Comandos (V, A, D, B sao as prioridades):" << std::endl;
    std::cout << "C <senha> <prioridade> <hh> <mm> (Ex: C P001 V 10 30)" << std::endl;
    std::cout << "A <hh> <mm> (Atender paciente. Ex: A 11 00)" << std::endl;
    std::cout << "D (Exibir o tamanho das filas)" << std::endl;
    std::cout << "Q (Sair)" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    
    
    while(std::cin >> x && x!='Q'){ 
        switch (x)
        {
        case 'C':
            std::cin >> dados.senha >> dados.prioridade >> dados.hh >> dados.mm;

            dados.total_minutos = dados.hh * 60 + dados.mm;

            if(dados.hh > 23 || dados.mm > 59 || dados.hh < 0 || dados.mm < 0){
                std::cout << " Hora de entrada invalida." << std::endl;
                break;
            }   
            cadastrar_paciente(dados);
            calcular_pico_lotacao();
            break;
            
        case 'A':
            std::cin >> atendimento.hh >> atendimento.mm;
            atendimento.total_minutos = atendimento.hh * 60 + atendimento.mm;

            if(atendimento.hh > 23 || atendimento.mm > 59 || atendimento.hh < 0 || atendimento.mm < 0){
                std::cout << "Hora de atendimento invalida." << std::endl;
                break;
            }
            atender_paciente(atendimento, atendimentos);
            break;
            
        case 'D':
            informacoes();
            break;
        
        default:
            std::cout << "Comando invalido. Use C, A, D ou Q." << std::endl;
            break;
        }
    }
    std::cout << "--- RELATORIO FINAL --- " << std::endl;
    std::cout << "Total atendidos: " << atendimentos << std::endl;
    std::cout << "Por prioridade: " 
              << "V=" << atendimentos_prioridadeV
              << " A=" << atendimentos_prioridadeA
              << " D=" << atendimentos_prioridadeD
              << " B=" << atendimentos_prioridadeB << std::endl;
    std::cout << "Pico de lotacao: " << pico_lotacao << std::endl;
    std::cout << "Espera maxima: " << espera << " min"<< std::endl;

    return 0;
}

// OBS : Não consegui consertar uma pequena coisa, quando o paciente é registrado por exemplo 08:00
// ele pode ser atendido as 07:59 e o sistema não bloqueia isso. Mas ai é um erro do usuario mesmo 😁.