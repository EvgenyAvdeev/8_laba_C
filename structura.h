 struct FIO {
	char NAME[10];
	char surname[10];
	char otch[10];
}; 

typedef struct {
	struct FIO author;
	char name[30];
	char redaction[30];
	char year[30];
	char page[30];
}book_info;
