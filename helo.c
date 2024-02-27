#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_epanalipsis 1000
#define elegxos 1e-6

// synartisi ypologismou polionimou me tin timi pou dinete sto x.

double polyonimo(double x, double *sintelestes, int vathmos) {
    double result = 0.0;
    for (int i = 0; i <= vathmos; i++) {                        //xrisimopoioume for gia na perasume apo tous orous toy polyonimou
        result += sintelestes[i] * pow(x, i);                   //prosthetume sto result ton sintelesti tou orou * x ipsomeno st i
    }
    return result;
}

// synartisi ypologismou paragogou me tin timi pou dinete sto x

double paragogos(double x, double *sintelestes, int vathmos) {    //dexete to x, ena pinaka sintelestwn, kai ton vathmo tou polyonimou
    double result = 0.0;
    for (int i = 1; i <= vathmos; i++) {                          //xrisimopoioume for gia na perasume apo tous orous toy polyonimou

        result += i * sintelestes[i] * pow(x, i - 1);             //prosthetume sto result tin timi pou vriskume me ton typo
    }
    return result;
}

// synartisi pou xrisimopioite i methodos newtonRaphson gia evresi tis rizas

double newtonRaphson(double *sintelestes, int vathmos, double arx_ektimisi) {
    double x0 = arx_ektimisi;
    double x1;
    int epanalipsis = 0;

    do {
        double fx = polyonimo(x0, sintelestes, vathmos);
        double paragogos_fx = paragogos(x0, sintelestes, vathmos);

        // elegxoume an i paragogos ine konta sto miden gia na apofigoume na exoume diereti miden

        if (fabs(paragogos_fx) < elegxos) {                          //xrisimopioiume fabs gia na parume tin apoliti timi

            printf("nan\n");

            return NAN;         //  syntomografia tou orou (Not a Number) stin platforma IEE754
        }

        // xrisimopoioume ton typo newtonraphson gia na parume tin epomeni proseggisi rizas
        x1 = x0 - fx / paragogos_fx;

        // elegxoume afairontas tis apolites times an i aferesi ine mikroteri tou 10 ipsomeno stin -6(def elegxos stin arxi tou programmatos)
        
        if (fabs(x1 - x0) < elegxos) {                   //xrisimopioiume fabs gia na parume tin apoliti timi
            return x1;                                   // epistrefume tin proseggisi
        }

        x0 = x1;                                         // allazume to x0 me tin nea proseggisi rizas pou vrikame
        epanalipsis++;                                   // auksanoume to counter ton epanalipseon

    } while (epanalipsis < MAX_epanalipsis);  //xrisimopoioume do while gia na diasfalisume oti den exume ipervei tis 1000 epanalipsis

    //se periptosi pou den vrume riza meta apo 1000 epanalipsis tote vgenume apo to do while tiponume minima pos den vrethike kai epistrefume NAN

    printf("incomplete\n");

    return NAN;  
}

// pernoume tous sintelestes tou polyonimou kai tin arxiki ektimisi os orismata apo tin grammi entolon

int main(int argc, char *argv[]) {

    // elegxos an einai sosta ta stoixia eisodou pou dosame os orismata apo tin grammi entolwn
    if (argc != 8) {
        printf("Usage: %s a0 a1 a2 a3 a4 a5 x0\n", argv[0]);
        return 1;                                                       // eksodos me exit code an den tirunte oi prodiagrafes

    }

    
    double sintelestes[6];                                              // pinakas pou apothikeuoume tous sintelestes tou polyonimou
    for (int i = 1; i <= 6; i++) {
        char *checking;                                                 //xrisimopoiite gia to conversion meso strod, o pointer tha dixni sto telefteo stixio p den egine convert
                                                                        //parola auta den tha kanume ton elegxo efoson i askisi mas leei pos den xriazete

        sintelestes[i - 1] = strtod(argv[i], &checking);                // xrisi strod gia metatropi ton orismaton eisodou kai apothikeusi ston pinaka sintelestwn

           }

    char *checking;
    double arx_ektimisi = strtod(argv[7], &checking);                   // metattropi me strtod kai apothikeusi os arxiki ektimisi
  
    // klisi tis sinartisis newtonRaphson gia evresi tis rizas
    double riza = newtonRaphson(sintelestes, 5, arx_ektimisi);

    // An vrethii riza tin tiponume 
    if (!isnan(riza)) {                                    //isnan sinartisi tis viliothikis math.c pou elegxei an i timi tis rizas ine nan(not a number)
                                                           //afou elegxoume oti den ine nan (!) tote tiponume
        printf("riza found: %.2f\n", riza);                //tiponume tin riza me dyo dekadika
    }

    return 0; 
}
