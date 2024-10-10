// ANDREA BARBIN 5°E PROGETTAZIONE LIBRERIA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX_LUNGH_STR 40
#define MAX_LIBRI 100
#define BUFFER_DIM 1024

// DEFINIZIONE ENUM PER LA CATEGORIA DEI LIBRI
typedef enum
{
    Narrativa,
    Scienza,
    Saggistica,
    Arte,
    Romanzo

} Categoria;

// DEFINIZIONE STRUCT PER MODELLARE UN LIBRO
typedef struct
{
    char titolo[MAX_LUNGH_STR];
    char autore[MAX_LUNGH_STR];
    int annoPubblicazione;
    float prezzo;
    Categoria cat;
} Libro;

// FUNZIONE CHE RITORNA LA CATEGORIA COME STRINGA
char *categoriaStringa(Categoria catCercata)
{
    switch (catCercata)
    {
    case Narrativa:
        return "Narrativa";

    case Scienza:
        return "Scienza";

    case Saggistica:
        return "Saggistica";

    case Arte:
        return "Arte";

    case Romanzo:
        return "Romanzo";

    default:
        return "Genere non presente nella libreria.";
    }
}

// FUNZIONE CHE RITORNA LA CATEGORIA PARTENDO DALLA STRINGA CORRISPONDENTE
Categoria stringaACategoria(const char *categoriaStr)
{

    if (strcmp(categoriaStr, "Narrativa") == 0)
    {
        return Narrativa;
    }
    else if (strcmp(categoriaStr, "Scienza") == 0)
    {
        return Scienza;
    }
    else if (strcmp(categoriaStr, "Saggistica") == 0)
    {
        return Saggistica;
    }
    else if (strcmp(categoriaStr, "Arte") == 0)
    {
        return Arte;
    }
    else if (strcmp(categoriaStr, "Romanzo") == 0)
    {
        return Romanzo;
    }
    else
    {
        return Narrativa;
    }
}

Libro libreria[MAX_LIBRI];

// FUNZIONE PER STAMPARE TUTTI I CAMPI UN SINGOLO LIBRO
void StampaLibro(Libro libro)
{
    printf("TITOLO: %s\n", libro.titolo);
    printf("AUTORE: %s\n", libro.autore);
    printf("Anno di pubblicazione: %d\n", libro.annoPubblicazione);
    printf("PREZZO: %.2f €\n", libro.prezzo);
    printf("Categoria: %s\n", categoriaStringa(libro.cat));
}

// FUNZIONE PER TROVARE UN LIBRO DAL TITOLO
int cercaConTitolo(char titolo[])
{

    /*Questo ciclo scorre l'array di libri e una volta trovato
    il libro con campo titolo uguale alla stringa che contiene il titolo cercato,
    questa funzione ritorna un valore intero pari all'indice corrispondente alla posizione del libro nell'array.*/

    for (int i = 0; i < MAX_LIBRI; i++)
    {

        // strcasecmp confronta le stringhe in maniera case insensitive (non considerando se i caratteri siano maiuscoli o minuscoli)
        if (strcasecmp(libreria[i].titolo, titolo) == 0)
        {
            return i;
        }
    }

    return -1; // Se il libro non viene trovato ritorna -1 per identificare chiaramente che il libro non è presente
}

// FUNZIONE CHE ALLOCA UN'AREA DI MEMORIA PER INSERIRE I LIBRI SCRITTI DA UN DETERMINATO AUTORE
Libro *cercaConAutore(char autore[], int *size, int nLibri)
{
    int libriScrittiCercato = 0;

    // Questo ciclo conta quanti libri sono scriti dall'autore ricercato.
    for (int i = 0; i < nLibri; i++)
    {

        /*La funzione strcasecmp(libreria[i].autore, autore) verifica in maniera case insensitive se il libro
        corrente ha il campo autore uguale alla stringa contenente l'autore desiderato. Se ritorna 0 significa che
        il libro corrente ha il campo autore uguale alla stringa passata come parametro.*/

        if (strcasecmp(libreria[i].autore, autore) == 0)
        {
            libriScrittiCercato++; // Conteggio dei libri dell'autore cercato
        }
    }

    // ALLOCAZIONE DELL'AREA DI MEMORIA PER I LIBRI DELL'AUTORE CERCATO
    Libro *arrayScrittiCercato = malloc(sizeof(Libro) * libriScrittiCercato);

    // Se il puntatore ha valore NULL si segnala l'errore e il programma termina l'esecuzione
    if (!arrayScrittiCercato)
    {
        printf("Si è verificato un'errore nell'allocazione di memoria per i libri con lo stesso autore.\n");
        exit(1);
    }

    int j = 0;

    // INSERIMENTO DEI LIBRI SCRITTI DALL'AUTORE CERCATO NELL'ARRAY ALLOCATO IN PRECEDENZA
    for (int i = 0; i < nLibri; i++)
    {
        if (strcasecmp(libreria[i].autore, autore) == 0)
        {
            arrayScrittiCercato[j++] = libreria[i];
        }
    }

    *size = libriScrittiCercato; // VIENE RITORNATA PER RIFERIMENTO LA DIMENSIONE DELL'ARRAY
    return arrayScrittiCercato;
}

// FUNZIONE PER STAMPARE UN'ARRAY DI LIBRI CONOSCENDO LA DIMENSIONE
void stampaArray(Libro *arrLibri, int size)
{

    for (int i = 0; i < size; i++)
    {
        StampaLibro(arrLibri[i]);
        printf("\n");
    }
}

// FUNZIONE CHE STAMPA TUTTI I LIBRI DELLA CATEGORIA CERCATA
void stampaCategoria(char categoria[], int nLibri)
{
    int libriCategoria = 0;

    /*Ciclo for scorrere l'array di libri e per verificare quali siano i libri della categoria cercata*/
    for (int i = 0; i < nLibri; i++)
    {

        /*strcasecmp(categoriaStringa(libreria[i].cat), categoria) controlla se il libro corrente ha il campo categoria uguale alla stringa
        che contiene la categoria cercata. categoriaStringa(libreria[i].cat) ritorna il valore della categoria ma in una stringa.*/

        if (strcasecmp(categoriaStringa(libreria[i].cat), categoria) == 0)
        {
            printf("\nLIBRO n° %d\n", (i + 1));
            StampaLibro(libreria[i]);
            libriCategoria++;
        }
    }
    if (libriCategoria == 0)
    {
        printf("Non è presente nessun libro della categoria %s nella libreria.\n", categoria);
    }
}

// FUNZIONE CHE ALLOCA UN'AREA DI MEMORIA PER I LIBRI CHE HANNO IL PREZZO COMPRESO NELL'INTERVALLO CERCATO
Libro *compresiNeiPrezzi(float prezzoMinimo, float prezzoMassimo, int *size, int nLibri)
{

    int libriCompresiPrezzi = 0; // Questa variabile serve per allocare l'area di memoria perchè viene moltiplicata per la dimensione in byte della struct Libro

    /*Ciclo for contare quanti libri hanno il prezzo compreso in un determinato intervallo.*/
    for (int i = 0; i < nLibri; i++)
    {
        if (libreria[i].prezzo >= prezzoMinimo && libreria[i].prezzo <= prezzoMassimo)
        {
            libriCompresiPrezzi++;
        }
    }

    // ALLOCAZIONE DELL'AREA DI MEMORIA PER I LIBRI CON IL PREZZO COMPRESO NELL'INTERVALLO CERCATO
    Libro *arrayCompresiPrezzo = malloc(sizeof(Libro) * libriCompresiPrezzi);

    // Se il puntatore ha valore NULL si segnala l'errore e il programma termina l'esecuzione
    if (!arrayCompresiPrezzo)
    {
        printf("Si è verificato un'errore nell'allocazione di memoria per i libri con il prezzo compreso nell'intervallo cercato.\n");
        exit(1);
    }

    // INSERIMENTO DEI LIBRI CON IL PREZZO COMPRESO NELL'INTERVALLO INSERITO NELL'ARRAY ALLOCATO IN PRECEDENZA
    int j = 0;
    for (int i = 0; i < nLibri; i++)
    {
        if (libreria[i].prezzo >= prezzoMinimo && libreria[i].prezzo <= prezzoMassimo)
        {
            arrayCompresiPrezzo[j++] = libreria[i];
        }
    }

    *size = libriCompresiPrezzi; // VIENE RITORNATA PER RIFERIMENTO LA DIMENSIONE DELL'ARRAY
    return arrayCompresiPrezzo;  // RITORNA IL PUNTATORE ALL'AREA DI MEMORIA ALLOCATA PER L'ARRAY
}

// FUNZIONE CHE ALLOCA UN'AREA DI MEMORIA PER I LIBRI CHE SONO STATI SCRITTI NELL'ANNO CERCATO
Libro *cercaAnnoPubb(int anno, int *size, int nLibri)
{

    int libriAnnoCercato = 0; // Questa variabile serve per allocare l'area di memoria perchè viene moltiplicata per la dimensione in byte della struct Libro

    /*Ciclo for contare quanti libri sono stati scritti nell'anno cercato.*/

    for (int i = 0; i < nLibri; i++)
    {
        if (libreria[i].annoPubblicazione == anno)
        {
            libriAnnoCercato++;
        }
    }

    // ALLOCAZIONE DELL'AREA DI MEMORIA PER I LIBRI SCRITTI NELL'ANNO CERCATO
    Libro *arrayAnnoCercato = malloc(sizeof(Libro) * libriAnnoCercato);

    // Se il puntatore ha valore NULL si segnala l'errore e il programma termina l'esecuzione
    if (!arrayAnnoCercato)
    {
        printf("Si è verificato un'errore nell'allocazione di memoria per i libri scritti nell'anno cercato.\n");
        exit(1);
    }

    // INSERIMENTO DEI LIBRI SCRITTI NELL'ANNO CERCATO NELL'ARRAY ALLOCATO IN PRECEDENZA
    int j = 0;

    for (int i = 0; i < nLibri; i++)
    {
        if (libreria[i].annoPubblicazione == anno)
        {
            arrayAnnoCercato[j++] = libreria[i];
        }
    }

    *size = libriAnnoCercato; // VIENE RITORNATA PER RIFERIMENTO LA DIMENSIONE DELL'ARRAY
    return arrayAnnoCercato;  // RITORNA IL PUNTATORE ALL'AREA DI MEMORIA ALLOCATA PER L'ARRAY
}

// FUNZIONE CHE LEGGE I DATI DAL FILE

int leggiCSV(const char *nomeFile)
{
    // Apertura del file in modalità lettura ("r") utilizzando il nome del file passato come parametro.
    FILE *file = fopen(nomeFile, "r");

    /*Se fopen restituisce NULL, significa che non è stato possibile aprire il file
    (es. file inesistente). In questo caso vine visualizzato l'errore e il programma termina l'esecuzione*/
    if (file == NULL)
    {
        printf("Errore nell'apertura del file.\n");
        exit(-1);
    }

    // Dichiarazione di un buffer per memorizzare temporaneamente le righe lette dal file.
    char buffer[BUFFER_DIM];

    // Variabile contatore per tenere traccia del numero di libri letti.
    int i = 0;

    // Salta la prima riga se è l'intestazione
    if (fgets(buffer, sizeof(buffer), file) == NULL)
    {
        printf("Errore: il file è vuoto o non è stato possibile leggere l'intestazione.\n");
        fclose(file);
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), file) && i < MAX_LIBRI)
    {
        // Se la riga è vuota, salta il ciclo
        if (strlen(buffer) == 0)
        {
            continue;
        }

        // Estrazione del primo token corrispondente al titolo del libro dalla riga, utilizzando ";" come delimitatore.
        char *token = strtok(buffer, ";");
        if (token != NULL)
        {
            // Copia del token estratto nel campo titolo dell'elemento corrente dell'array.
            strcpy(libreria[i].titolo, token);
        }
        else
        {
            printf("Errore: titolo mancante nella riga %d\n", i + 2);
            break; // Interrompe il ciclo se il titolo è mancante
        }

        // Estrazione del secondo token corrispondente all'autore del libro e memorizzazione nel campo autore dell'elemento corrente dell'array.
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            strcpy(libreria[i].autore, token);
        }
        else
        {
            printf("Errore: autore mancante nella riga %d\n", i + 2);
            break; // Interrompe il ciclo se l'autore è mancante
        }

        /*Estrazione del terzo token, corrispondente all'anno di pubblicazione, e conversione in intero con atoi
        per l'inserimento nel campo annoPubblicazione della posizione corrente nell'array*/

        token = strtok(NULL, ";");
        if (token != NULL)
        {
            libreria[i].annoPubblicazione = atoi(token);
        }
        else
        {
            printf("Errore: anno mancante nella riga %d\n", i + 2);
            break; // Interrompe il ciclo se l'anno è mancante
        }

        /*Estrazione del quarto token, corrispondente al prezzo del libro, e conversione in float con atof
        per l'inserimento nel campo prezzo della posizione corrente nell'array*/
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            libreria[i].prezzo = atof(token);
        }
        else
        {
            printf("Errore: prezzo mancante nella riga %d\n", i + 2);
            break; // Interrompe il ciclo se il prezzo è mancante
        }

        // Estrazione del quinto token, corrispondente alla categoria del libro. Potrebbe non essere presente.
        token = strtok(NULL, ";");
        if (token != NULL)
        {
            // Rimozione di eventuali caratteri di nuova linea presenti nel token.
            token[strcspn(token, "\r\n")] = 0;

            // Conversione della stringa in un valore di tipo categoria e assegnazione al campo cat della posizione corrente dell'array.
            libreria[i].cat = stringaACategoria(token);
        }
        else
        {
            libreria[i].cat = 0; // Imposta una categoria di default se mancante
        }

        i++; // Viene incrementato il contatore per tenere traccia del numero di libri letti dal file e inseriti nell'array
    }

    fclose(file); // CHIUSURA DEL FILE
    return i;     // La funzione restituisce il numero di libri letti dal file e inseriti nell'array
}

int main(int argc, char *argv[])
{

    /*Se argc è minore di 2 significa che l'inserimento del nome del file da cui leggere i dati dei libri in argv[1]
    non è andato a buon fine. In questo caso viene segnalato l'errore e il programma termina l'esecuzione*/

    if (argc < 2)
    {
        printf("Inserimento del nome del file di origine errato.\n");
        exit(0); // Uscita dal programma
    }

    /*La funzione leggiCSV ritorna un valore intero che identifica il numero di libri letti dal file e inseriti nell'array*/

    int nLibri = leggiCSV(argv[1]);
    int continua = 1;
    int opzione;

    while (continua)
    {
        printf("\n|============GESTIONE LIBRERIA============|");
        printf("\n[1] Cerca un libro\n");
        printf("[2] Visualizzare i libri di una certa categoria.\n");
        printf("[3] Esci dall'archivio.\n");

        // Ciclo do-while per ripetere l'inserimento del'opzione in caso sia stato svolto in maniera errata
        do
        {
            printf("\nInserire un'opzione: \n");
            scanf("%d", &opzione);

            // Segnalazione di errore nel caso dell'inserimento di un errore errato
            if (opzione < 1 || opzione > 3)
            {
                printf("L'opzione selezionata non esiste.\n");
            }

        } while (opzione < 1 || opzione > 3);

        switch (opzione)
        {

        // RICERCA DEL LIBRO
        case 1:
        {
            int ricercaOpzione = 0;

            printf("\nScegliere il criterio della ricerca:\n[1] Autore\n");
            printf("[2] Titolo\n");
            printf("[3] Prezzo\n");
            printf("[4] Anno di pubblicazione\n");
            printf("[5] Uscita dalla ricerca\n");

            // Ciclo do-while per ripetere l'inserimento del'opzione in caso sia stato svolto in maniera errata
            do
            {
                printf("\nSelezionare il criterio di ricerca.\n");
                scanf("%d", &ricercaOpzione);

                // Segnalazione di errore nel caso dell'inserimento di un errore errato
                if (ricercaOpzione < 1 || ricercaOpzione > 5)
                {
                    printf("Opzione errata\n");
                }

            } while (ricercaOpzione < 1 || ricercaOpzione > 5);

            // SWITCH CASE PER L'OPZIONE DI RICERCA
            switch (ricercaOpzione)
            {

            // RICERCA PER AUTORE
            case 1:
            {

                char autoreCercato[MAX_LUNGH_STR];

                printf("Inserire il nome dell'autore:\n");

                scanf(" %[^\n]s", autoreCercato); // Il segnaposto %[^\n]s permette di inserire una stringa contenente spazi

                int size; // Variabile per la dimensione dell'array, viene modificata per riferimento dalla funzione cercaConAutore(autoreCercato, &size, nLibri)

                Libro *scrittiDaCercato = cercaConAutore(autoreCercato, &size, nLibri);
                /*Il puntatore *scrittiDaCercato viene inizializzato con l'indirizzo dell'area allocata da *cercaConAutore,
                corrispondente all'array contenente i libri scritti dall'autore cercato.*/

                if (size == 0)
                {
                    printf("Nesssun libro della libreria è stato scritto dall'autore cercato.\n");
                }
                else
                {
                    printf("\nLibri scritti da %s:\n", autoreCercato);
                    stampaArray(scrittiDaCercato, size); // Output dell'array dei libri scritti dall'autore cercato
                }
                free(scrittiDaCercato); // VIENE LIBERATA LA MEMORIA ALLOCATA DA cercaConAutore(autoreCercato, &size, nLibri)
                break;
            }

            // RICERCA PER TITOLO
            case 2:
            {
                char titoloCercato[MAX_LUNGH_STR];
                printf("\nInserire il titolo del libro desiderato: \n");
                scanf(" %[^\n]s", titoloCercato); // Il segnaposto %[^\n]s permette di inserire una stringa contenente spazi

                int indiceLibroDaTitolo = cercaConTitolo(titoloCercato);

                /*cercaConTitolo(titoloCercato) ritorna l'indice, se questo è negativo (nello specifico = -1),
                significa che il libro non è stato trovato.*/

                if (indiceLibroDaTitolo < 0)
                {

                    printf("Il libro cercato non è presente nella libreria.\n");
                }
                else
                {
                    printf("\nEcco il libro cercato:\n");
                    StampaLibro(libreria[indiceLibroDaTitolo]); // Output del libro trovato
                }
                break;
            }

            // RICERCA PER INTERVALLO DI PREZZO
            case 3:
            {

                float prezzoMinimo, prezzoMassimo;

                // Ciclo do-while per ripetere l'inserimento del prezzo MINIMO in caso sia stato svolto in maniera errata
                do
                {
                    printf("\nInserire un prezzo minimo:\n");
                    scanf("%f", &prezzoMinimo);

                    // Segnalazione di errore nel caso il prezzo MINIMO non sia inserito correttamente
                    if (prezzoMinimo < 0)
                    {
                        printf("Errore nell'inserimento del prezzo.\n");
                    }

                } while (prezzoMinimo < 0);

                // Ciclo do-while per ripetere l'inserimento del prezzo MASSIMO in caso sia stato svolto in maniera errata
                do
                {
                    printf("\nInserire un prezzo massimo:\n");
                    scanf("%f", &prezzoMassimo);

                    // Segnalazione di errore nel caso il prezzo MASSIMO non sia inserito correttamente
                    if (prezzoMassimo < 0 || prezzoMassimo < prezzoMinimo)
                    {
                        printf("Errore nell'inserimento del prezzo.\n");
                    }

                } while (prezzoMassimo < 0 || prezzoMassimo < prezzoMinimo);

                int size; // Variabile per la dimensione dell'array, viene modificata per riferimento dalla funzione compresiNeiPrezzi(prezzoMinimo, prezzoMassimo, &size, nLibri)
                Libro *compresiIntervallo = compresiNeiPrezzi(prezzoMinimo, prezzoMassimo, &size, nLibri);

                /*Il puntatore *compresiIntervallo viene inizializzato con l'indirizzo dell'area allocata da
                CompresiNeiPrezzi(prezzoMinimo, prezzoMassimo, &size, nLibri),
                corrispondente all'array contenente i libri aventi il prezzo compreso nell'intervallo inserito.*/

                if (size > 0)
                {
                    printf("\nLibri compresi tra %f e %f euro:\n", prezzoMinimo, prezzoMassimo);
                    stampaArray(compresiIntervallo, size); // Output dell'array dei libri con il prezzo compreso nell'intervallo
                }
                else
                {
                    printf("Nessun libro ha il prezzo compreso nell'intervallo cercato.\n");
                }

                free(compresiIntervallo); // VIENE LIBERATA LA MEMORIA ALLOCATA DA CompresiNeiPrezzi(prezzoMinimo, prezzoMassimo, &size, nLibri)
                break;
            }

            // RICERCA PER ANNO DI PUBBLICAZIONE
            case 4:
            {
                int annoPubb;

                // Ciclo do while per la ripetizione dell'inserimento dell'anno di pubblicazione in caso avvenga in maniera errata
                do
                {
                    printf("Inserire l'anno di pubblicazione\n");
                    scanf("%d", &annoPubb);

                    // Segnalazione di errore in caso di errore nell'inserimento dell'anno di pubblicazione
                    if (annoPubb < 0)
                    {
                        printf("Il formato dell'anno inserito non è corretto.\n");
                    }

                } while (annoPubb < 0);

                int size; // Variabile per la dimensione dell'array, viene modificata per riferimento dalla funzione cercaAnnoPubb(annoPubb, &size, nLibri)
                Libro *libriAnnoCercato = cercaAnnoPubb(annoPubb, &size, nLibri);

                /*Il puntatore *libriAnnoCercato viene inizializzato con l'indirizzo dell'area allocata da
                cercaAnnoPubb(annoPubb, &size, nLibri), corrispondente all'array contenente i libri scritti
                nell'anno inserito.*/

                if (size > 0)
                {
                    printf("\nLibri pubblicati nel %d:\n", annoPubb);
                    stampaArray(libriAnnoCercato, size); // Output dell'array scritti nell'anno cercato
                }
                else
                {
                    printf("Nessun libro è stato pubblicato nell'anno cercato.\n");
                }

                free(libriAnnoCercato); // VIENE LIBERATA LA MEMORIA ALLOCATA DA ccercaAnnoPubb(annoPubb, &size, nLibri)

                break;
            }

            // USCITA DALLA MODALITA' RICERCA
            case 5:
            {
                printf("Uscita dalla ricerca.\n");
                break;
            }
            }
            break;
        }

        // OUTPUT LIBRI DI UNA DETERMINATA CATEGORIA
        case 2:
        {

            char catCercata[MAX_LUNGH_STR];
            printf("Inserire la categoria desiderata: \n");
            scanf(" %[^\n]s", catCercata); // Il segnaposto %[^\n]s permette di inserire una stringa contenente spazi
            stampaCategoria(catCercata, nLibri);

            break;
        }

        // USCITA DAL CICLO E DAL PROGRAMMA
        case 3:
        {
            continua = 0;
            break;
        }
        }

        printf("\n--------------------------------\n");
    }
    return 0;
}
