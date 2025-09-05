# Controller di gioco basato su Arduino e comunicazione via seriale con motore di gioco custom

Questo è il firmware del mio controller di gioco, consistente in un controller Arduino UNO collegato a un pulsante e un rotary encoder. 

Il codice legge continuamente gli input dell'utente e li invia sotto forma di pacchetti seriali a un game engino custom che li elabora aggiornando poi l'input-state di gioco.

È possibile visionare sia il codice relativo al firmware che la funzione specifica che riceve i pacchetti e ne estrae i contenuti. 
