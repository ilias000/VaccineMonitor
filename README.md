## ΓΕΝΙΚΕΣ ΟΔΗΓΙΕΣ
### Θεωρώ δεδομένο ότι η :
- εντολή εκτέλεσης θα είναι της μορφής : 
./vaccineMonitor -c citizenRecordsFile –b bloomSize 
                    ή 
./vaccineMonitor –b bloomSize -c citizenRecordsFile

- το citizenRecordsFile θα δωθεί χωρίς .txt extension

---
```c++
if (argc < 5)
{
    cout << "Gamiese" << endl;
    return 0;
}
```
---