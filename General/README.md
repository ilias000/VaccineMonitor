## **Προγραμματισμός Συστήματος - 1η Εργασία, Εαρινό Εξάμηνο 2021**
---
### **Όνομα :   Ηλίας**
### **Επώνυμο : Πιοτόπουλος**
### **Α.Μ. :    1115201800335**

---

## **ΓΕΝΙΚΕΣ ΟΔΗΓΙΕΣ**
### Θεωρώ δεδομένο ότι :
- η εντολή εκτέλεσης θα είναι της μορφής :     
    - ./vaccineMonitor -c citizenRecordsFile –b bloomSize   
                    ή 
    - ./vaccineMonitor –b bloomSize -c citizenRecordsFile  

- το citizenRecordsFile θα δωθεί χωρίς .txt extension.  
- για να αλαχτεί το όνομα του citizenRecordsFile σε κάποιο άλλο αρχείο, πρέπει να αλλαχτεί στο Makefile η τμή του :   
```Makefile
FILE = -c citizenRecordsFile
```   
σε  
```Makefile
FILE = -c *καινούριο_όνομα_αρχείου*
```  
- για να αλαχτεί το μέγεθος του bloom filter σε *bytes*, πρέπει να αλλαχτεί στο Makefile η τμή του :      
```Makefile
BLOOMSIZE = -b 100000
```  
 σε   
```Makefile
BLOOMSIZE = -b *καινούριο_μέγεθος_bloom_filter_σε_bytes*
```
 - για να αλαχτεί η εντολή εκτέλεσης απο :  
 ```./vaccineMonitor -c citizenRecordsFile –b bloomSize```  
 σε  
 ```./vaccineMonitor –b bloomSize -c citizenRecordsFile```  
 πρέπει να αλλαχτεί στο Makefile το :  
 ```Makefile
 run: 
	./$(PROGRAM) $(FILE) $(BLOOMSIZE)
```
σε
```Makefile
run: 
	./$(PROGRAM) $(BLOOMSIZE) $(FILE)
```

#### **Μεταγλώττιση & Εκτέλεση**
- Eντολή Μεταγλώττισης :
```terminal
make
```
- Εντολή Εκτέλεσης :
```terminal
make run
```
- Εντολή Καθαρισμού :
```terminal
make clean
```

## **Script**
### ΓΕΝΙΚΕΣ ΠΛΗΡΟΦΟΡΙΕΣ
- η εντολή εκτέλεσης θα είναι της μορφής :   
  - ./testFile.sh virusesFile.txt countriesFile.txt 100 1  
- Γίνεται έλεγχος για το αν έχουν δωθεί και τα 4 arguments που πρέπει.  
- Γίνεται έλεγχος για το αν υπάρχει το αρχείο virusesFile.  
- Γίνεται έλεγχος για το αν υπάρχει το αρχείο countriesFile.  
- Αν ο χρήστης θέλει να υπάρχουν duplicate ids βρίσκω για κάθε record έναν αριθμό τυχαία από το 0 έως και το 5 και αν έρθει το 1 τότε το  
συγκεκριμένο record θα έχει για id ένα id που έχει ξανά χρησιμοποιθεί αλλιώς θα έχει διαφορετικό.  
- Τα ids που είναι duplicate έχουν περισσότερες πιθανότητες να ξανά γίνουν duplicate αφού θα υπάρχουν πάνω απο μία φορά στο πίνακα με τα ids.  
- Αν για το συγκεκριμένο record ο citizen δεν έχει κάνει το εβόλιο βρίσκω τυχαία έναν αριθμό από το 0 έως και το 5 και αν έρθει το 1 τότε   
θα βάλω και ημερομινία οπότε θα είναι inconsistent.


---
```c++
if (argc < 5)
{
    cout << "Hello world !" << endl;
    return 0;
}
```
---
