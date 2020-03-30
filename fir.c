#include "fir.h"
#include "fichiers.h"


absorp firTest(char* filename){
    FILE* data = initFichier(filename);
    absorp myAbsorp = {0, 0, 0, 0}, fileValues;
    int state = 0;
    Queue* queue = CreateQueue();
    while(state != EOF){
        fileValues = lireFichier(data, &state);
        if(state == 6){
            myAbsorp = fir(fileValues, queue);
        }
    }
    DeleteQueue(queue);
	finFichier(data);
	return myAbsorp;
}

absorp fir(absorp myAbsorp, Queue* queue){
    const double FIR_TAPS[51]={1.4774946e-019, 1.6465231e-004, 3.8503956e-004, 7.0848037e-004, 1.1840522e-003, 1.8598621e-003, 2.7802151e-003, 3.9828263e-003, 5.4962252e-003, 7.3374938e-003, 9.5104679e-003, 1.2004510e-002, 1.4793934e-002, 1.7838135e-002, 2.1082435e-002, 2.4459630e-002, 2.7892178e-002, 3.1294938e-002, 3.4578348e-002, 3.7651889e-002, 4.0427695e-002, 4.2824111e-002, 4.4769071e-002, 4.6203098e-002, 4.7081811e-002, 4.7377805e-002, 4.7081811e-002, 4.6203098e-002, 4.4769071e-002, 4.2824111e-002, 4.0427695e-002, 3.7651889e-002, 3.4578348e-002, 3.1294938e-002, 2.7892178e-002, 2.4459630e-002, 2.1082435e-002, 1.7838135e-002, 1.4793934e-002, 1.2004510e-002, 9.5104679e-003, 7.3374938e-003, 5.4962252e-003, 3.9828263e-003, 2.7802151e-003, 1.8598621e-003, 1.1840522e-003, 7.0848037e-004, 3.8503956e-004, 1.6465231e-004, 1.4774946e-019};
    absorp newAbsorp = myAbsorp;
    newAbsorp.acr = 0;
    newAbsorp.acir = 0;
    EnQueue(queue, myAbsorp);
    unsigned short size = queueSize(queue);
    for (unsigned short i = 0; i < size; ++i) {
        newAbsorp.acr += (float)(FIR_TAPS[i] * getValue(queue, size-1-i).acr);
        newAbsorp.acir += (float)(FIR_TAPS[i] * getValue(queue, size-1-i).acir);
    }
    return newAbsorp;
}