# compito-tpsit

##cosa andavaa realizzato
realizzare un programma di lettura di una specifica linea di un file ( specificato nel codice ) presente sul server. Il server dovrà gestire connessioni da parte di più client e dovrà visualizzare l'IP di quelli connessi e il numero di riga del file richiesto, il client dovrà visualizzare a video la linea ricevuta dal server. Sia il client e il server dovranno visualizzare a video se l'operazione si è conclusa con successo oppure altrimenti.
Per ottenere una valutazione più alta si può realizzare una versione del client asincrona rispetto alla richiesta al server. In sostanza il client non si dovrà bloccare attendendo la risposta del server ma nel frattempo dovrà eseguire altre operazioni.

##come è stato realizato:

###lato client
è stata realizzata un applicazione che, all'avvio, si connette ad un server mandando ad esso la riga richiesta. In seguito essa laci un thread che rimane in attesa della risposta da parte del server mentre essa continua a valorare su altre operazioni. Per effettuare la connessione sono state utilizzate le librerie WinSock 32 di Microsoft che permettono di utilizzare le connessioni Socket in C. Il tutto funziona sulla porta 27000

###server
è stata realizzata un applicazione che, all'avvio, si mette in ascolto sulla porta 27000. Ogni qualvolta che un client si connette l'applicativo manda in esecuzione un thread per la sua gestione. Il claaienta manda un messaggio contenente la riga del file. Il Server, attraverso la funzione ifStream, legge il file fino alla riga richiesta e la restituisce. Il server restituisce il riusltato. Per effettuare la connessione sono state utilizzate le librerie WinSock 32 di Microsoft che permettono di utilizzare le connessioni Socket in C. Il tutto funziona sulla porta 27000
