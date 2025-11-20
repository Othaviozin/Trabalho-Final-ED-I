#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <queue>


struct  paciente
{
    std::string senha;
    char prioridade;
    int hh;
    int mm;
};

struct atendimento
{
    int hh;
    int mm;
};

std::queue<paciente> FilaV; // Fila de emergência
std::queue<paciente> FilaA; // Fila Urgente
std::queue<paciente> FilaD; // Fila Pouco Urgente
std::queue<paciente> FilaB; // Fila não urgente

int cadastrar_paciente(const paciente &dados){
    

}

int atender_paciente(const atendimento &atendimento){
    //code
}

int informacoes(){


}


int main(){

    char x;
    paciente dados;
    atendimento atendimento; 
    
    
    
    while(std::cin >> x && x!='Q'){ 
        switch (x)
        {
        case 'C':
            std::cin >> dados.senha >> dados.prioridade >> dados.hh >> dados.mm;
            cadastrar_paciente(dados);
            break;
        case 'A':
            std::cin >> atendimento.hh >> atendimento.mm;
            atender_paciente(atendimento);
            break;
        case 'D':
            informacoes();
            break;
        
        default:
            break;
        }

    }

    return 0;

}
