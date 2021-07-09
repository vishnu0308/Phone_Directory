/*
  Author: Karyampudi Venkata Vishnu Shravan
  Roll No: 1903124
  Date: 24-10-2020
  Description: This code works as a phone directory. It enables users to add, search and modify contacts.
*/
#include <stdio.h>
#include <stdlib.h>
//structure to store phone number and comment
struct ph_no
{
    char ph_no[50];
    char comment[50];
};

struct ph_dir
{
    char name[50];             //name will be stored here
    int no;                    //no. of contacts will be stored here. Printing this in file helps while reading from file.
    struct ph_no *ph_list_poi; //pointer to an array of above ph_no structure. All ph no's and comments will be stored in it.
};

/*
	add()
	Description: Adds a person's contact details to the directory.txt file.
				 All the details of a person are stored in a line.
	Line in file: Name\tnumber to identify no. of contacts ph.no. contact\t.......
	Output: returns 1 if contact is added.
*/
int add()
{
    int no, du1;
    char dum;
    struct ph_dir contact; //structure variable contact is initialised.
    FILE *fpoi_a;
    fpoi_a = fopen("phdir.txt", "a"); //opening file in append mode.closed in line 61.
    printf("----------------------------------------------------\n");
    printf("Enter name:");
    scanf(" %[^\n]", contact.name); //storing name input into structure contact
    printf("How many phone numbers you want to add:");
    scanf(" %d", &no); //storing num. of contacts in 'no'
    //making the pointer in contact struct variable point to array containing 'no' ph_no structures
    contact.ph_list_poi = (struct ph_no *)malloc(no * sizeof(struct ph_no)); //freed in line 62
    /*Below for loop:
	  Using a for loop storing each phone no. and comment in a ph_no struct variable and copying the contents 
	  of it into the respective index in array of structures created above.
	*/
    for (int k = 1; k <= no; k++)
    {
        struct ph_no num;
        printf("Enter number %d:", k);
        scanf(" %s", num.ph_no);
        printf("Add a comment:");
        scanf(" %[^\n]", num.comment);
        scanf("%c", &dum);
        contact.ph_list_poi[k - 1] = num;
    }
    //appending all details collected above into phdir.txt using fprintf
    fprintf(fpoi_a, "%s\t%d ", contact.name, no);
    for (int j = 0; j < no - 1; j++)
    {
        fprintf(fpoi_a, "%s %s\t", contact.ph_list_poi[j].ph_no, contact.ph_list_poi[j].comment);
    }
    fprintf(fpoi_a, "%s %s\n", contact.ph_list_poi[no - 1].ph_no, contact.ph_list_poi[no - 1].comment);
    fclose(fpoi_a);
    free(contact.ph_list_poi);
    return 1;
}

/*
	str_comp
	Description: Compares two strings if they are same.
	Inputs: pointers to two string arrays
	Output:Returns 0 : if not same
			       1 : if same  
*/
int str_comp(char *ptr1, char *ptr2)
{
    //Compare letters in one string with other until the longer word ends
    for (int k = 0; ((ptr1[k] != '\0') || (ptr2[k] != '\0')); k++)
    {
        if (ptr1[k] != ptr2[k])
        {
            return 0;
        }
    }
    return 1;
}
/*
	search()
	Inputs,Outputs: None
	Description:Prompts user to enter the name they want to search in phone directory.
				Checks that name in the file and prints the details of the contact if found.
				Else prints no entry found.
*/
void search()
{
    char str[50];
    char temp_str[50];
    char waste[1000];
    char waste1[1000];
    int temp, status, line = 1, k, che = 0;
    char temp_no[50], temp_comment[50];
    FILE *fpoi_s;
    FILE *fpoi_s2;
    fpoi_s = fopen("phdir.txt", "r"); //Opening file to read..closed in line 144.
    if (fpoi_s == NULL)
    {
        printf("No contacts in your phone directory!\n");
        return;
    } //checking if no such file exists
    printf("Enter name:");
    scanf(" %[^\n]", str); //took name from the user
    /*
		While adding whole data of a person would be added into a single line in the file. Next person's data
		would be added in the next line. Form of a line: Name\tno. ph.no comment\tph.no comment\t....(no such comments)..
		Below While loop:
			Reads each line from the file and stores it into two variables- one for name(ends by tab) and the other one to store
			remaining line as a string.Each time that name variable would be compared with the one given by the user to search
			by using str_comp function defined above. This loop continues until pointer reaches EOF(end of file) or the name matches
			with a name in the file(sets the status variable to 1).Variable 'line ' initialised to 1, gets incremented every time
			loop runs. If the name is found, value of line is the line in file at which the data of the person is present.
	*/
    while (fscanf(fpoi_s, "%[^\t]\t%d %[^\n]\n", temp_str, &temp, waste) != EOF)
    {
        che = 1; //it is used to know if file is empty.
        if (str_comp(str, temp_str) == 1)
        {
            status = 1;
            break;
        }
        line++;
    }
    if (che == 0)
    {
        printf("Your directory is empty.\n");
        return;
    }
    if (status == 1)
    {                                      //The name has matched.
        fpoi_s2 = fopen("phdir.txt", "r"); //opening the file again to read. Closed in line 139.
        printf("Entry found.\nName:%s\n", str);
        printf("___________________________________________________\n");
        printf("Phone Number \t Comment\n");
        printf("___________________________________________________\n");
        for (k = 1; k < line; k++)
        { //moving the pointer to the required line
            fscanf(fpoi_s2, "%[^\n]\n", waste1);
        }
        fscanf(fpoi_s2, "%[^\t]\t%d ", waste1, &line); //taking name and no of contacts. No of contacts is being stored in line(reuse)
        //Reading the phone no and comment "no of contacts-1" times(excluding last no. and comment) and each time printing it.
        for (int k = 0; k < line - 1; k++)
        {
            fscanf(fpoi_s2, "%s %[^\t]\t", temp_no, temp_comment);
            printf("%s \t %s\n", temp_no, temp_comment);
        } /*Reading last no. and comment and printing. Last no. and comment can't be read above because other comments
		end with tab and last comment ends with \n. As the format is different it is read differently. Everytime in 
		this code, last phone no. and comment will be read seperately.
		*/
        fscanf(fpoi_s2, "%s %[^\n]\n", temp_no, temp_comment);
        printf("%s \t %s\n", temp_no, temp_comment);
        fclose(fpoi_s2);
    }
    else
    { //status!=1
        printf("Sorry! No entries found for %s\n", str);
    }
    fclose(fpoi_s);
}
/*
	modify()
	Inputs,output:none
	Description: Prompts user to give the name of the contact to modify. Then user gets the choice to add a number or
				remove a number, modify name or phone number or comment.
*/
void modify()
{
    char name[50], each_line[20][1000];
    int k = 0, no_of_contacts, m;
    char temp_name[50];
    int temp = -1;
    char waste[100];
    int status = 0;
    int line = 1;
    struct ph_no ph;
    char ch;
    int del;
    int mod;
    char ans;
    int fi = 0;
    struct ph_dir contact;
    int r = 0;
    FILE *f1 = fopen("phdir.txt", "r"); //opening file to read. Closed at line 172.
    FILE *f2;
    FILE *f3;
    FILE *f4;
    FILE *f5;
    FILE *f6;
    FILE *f7;
    if (f1 == NULL)
    {
        printf("You haven't created your directory yet. You can do it by adding a contact.\n");
        return;
    } //checking if no such file exists.
    printf("Enter the name of the contact you want to modify:");
    scanf(" %[^\n]", name); //taking the name of the contact to modify.
    /*
	Below while loop reads for the name in the file, the variable line becomes the line no. at which the contact is
	present(if present). If the file is empty the  variable fi(initialised to 0) won't become 1. It is used to check if file is empty.
	*/
    while (fscanf(f1, "%[^\t]\t%d %[^\n]\n", temp_name, &temp, waste) != EOF)
    {
        fi = 1;
        if (str_comp(name, temp_name) == 1)
        {
            status = 1;
            break;
        }
        line++;
    }
    fclose(f1);
    if (fi == 0)
    {
        printf("File is empty.\n");
        return;
    }
    if (status != 1)
    { //checking if entry not found and printing it.
        printf("No entries found for %s\n", name);
        return;
    }
    f7 = fopen("phdir.txt", "r"); //opening file in read mode.Closed at line 191.
    /*
		Firstly, I declared a struct phdir variable to store the details of the person in the line no. stored
		above. The while loop in line no. ___ does this with a loophole. It can't store the details if the 
		required line is 1. So, I am taking the contents of the first line into the declared structure variable.
		If this is not the required line then the structure variable gets updated in the while loop in line ___.
		If this is the line required then we got our required data.
	*/
    fscanf(f7, "%[^\t]\t%d ", contact.name, &no_of_contacts);
    contact.ph_list_poi = (struct ph_no *)malloc(no_of_contacts * sizeof(struct ph_no));
    for (m = 0; m < no_of_contacts - 1; m++)
        fscanf(f7, "%s %[^\t]\t", contact.ph_list_poi[m].ph_no, contact.ph_list_poi[m].comment);
    fscanf(f7, "%s %[^\n]\n", contact.ph_list_poi[m].ph_no, contact.ph_list_poi[m].comment);
    fclose(f7);
    f3 = fopen("phdir.txt", "r"); //closed at line line 214.
    /*
		Already, first line's data is stored in the struct variable . Now, objective is to go to the required line
		and collect data from it into struct variable. Only we require 1 line of data. All other data will be stored in
		a two dimensional character array(each_line). Whole line will be considered as a single string and added in the
		respective index. If the file pointer comes to the line of name(which user wants to modify), then it will be skipped
		(instead,that line details gets updated in the structure variable.) Next whole line string would be stored in this
		index where we are supposed to take the line which user wants to modify. Idea is, we left the line to be modified
		and collected all other lines into an array of strings. We'll write this into the phdir.txt so that, all lines except
		the (to be modified) line will be written. After modifing the line in the structure, we'll append it at the end of file.
	*/
    while (fscanf(f3, "%[^\n]\n", each_line[k]) != EOF)
    {
        if (k == line - 2)
        { //condition for required line.
            fscanf(f3, "%[^\t]\t%d ", contact.name, &no_of_contacts);
            contact.ph_list_poi = (struct ph_no *)malloc(no_of_contacts * sizeof(struct ph_no)); //storing name and no. of no's
            for (m = 0; m < no_of_contacts - 1; m++)                                             //storing all ph no's, no's except the last
                fscanf(f3, "%s %[^\t]\t", contact.ph_list_poi[m].ph_no, contact.ph_list_poi[m].comment);
            fscanf(f3, "%s %[^\n]\n", contact.ph_list_poi[m].ph_no, contact.ph_list_poi[m].comment); //storing the last one.
        }
        k++;
    }

    fclose(f3);
    //As said above, writing all the lines(except required) into phdir.txt.
    f4 = fopen("phdir.txt", "w"); //opening file in write mode.Closed at line 226.
    /*
		All the lines except the selected line would be in each_line array. Writing the string at each index of array 
		to file does the job. But if the name from the user belongs to line 1 ,problem arises. The problem is line 1 is always 
		at index 0 of each_line array.So, the below if condition is used.
	*/
    if (line == 1)
        r = 1; //r corresponds to starting index.
    for (int j = r; j < k; j++)
    {
        fprintf(f4, "%s\n", each_line[j]);
    }
    fclose(f4);
    printf("Existing details are:\n"); //printing existing details.
    printf("S.No\tPhone no.\tComment\n");
    for (int h = 0; h < no_of_contacts; h++)
    {
        printf("%d\t%s\t%s\n", h + 1, contact.ph_list_poi[h].ph_no, contact.ph_list_poi[h].comment);
    }
    printf("For adding a new number to the contact, enter 'A' or 'a'\n");
    printf("To remove an existing number, enter 'R' or 'r'\n");
    printf("To modify name or particular number or comment, enter 'M' or 'm'\n");
    printf("Enter your choice: ");
    scanf(" %c", &ch);
    if (ch == 'A' || ch == 'a')
    {                                                                                                              //Adding additional comment and ph. no. to the name.
        no_of_contacts++;                                                                                          //incrementing it because we're adding a new no.
        contact.ph_list_poi = (struct ph_no *)realloc(contact.ph_list_poi, no_of_contacts * sizeof(struct ph_no)); //allocating extra memory in the structure.
        //taking details.
        printf("Enter number:");
        scanf(" %s", contact.ph_list_poi[no_of_contacts - 1].ph_no);
        printf("Enter comment:");
        scanf(" %[^\n]", contact.ph_list_poi[no_of_contacts - 1].comment);
        f2 = fopen("phdir.txt", "a"); //opening file to append the modified details in the structure. Closing at line 252.
        fprintf(f2, "%s\t%d ", contact.name, no_of_contacts);
        for (int p = 0; p < no_of_contacts - 1; p++)
        {
            fprintf(f2, "%s %s\t", contact.ph_list_poi[p].ph_no, contact.ph_list_poi[p].comment);
        }
        fprintf(f2, "%s %s\n", contact.ph_list_poi[no_of_contacts - 1].ph_no, contact.ph_list_poi[no_of_contacts - 1].comment);
        printf("Number added successfully\n");
        fclose(f2);
    }
    if (ch == 'R' || ch == 'r')
    { //Removing a number and a comment
        printf("Enter the S.No of the no. you want to delete:");
        scanf(" %d", &del);
        no_of_contacts--;                                     //decrementing since we are removing a no. and comment.
        f5 = fopen("phdir.txt", "a");                         //opening phdir.txt in append mode.Closed at 267.
        fprintf(f5, "%s\t%d ", contact.name, no_of_contacts); //appended name and contacts num.
        for (int j = 0; (j < no_of_contacts); j++)
        {
            if (j == del - 1)
                continue; //except the selected num, adding all
            fprintf(f5, "%s %s\t", contact.ph_list_poi[j].ph_no, contact.ph_list_poi[j].comment);
        }
        if ((del - 1) != no_of_contacts) //adding last no. and comment by checking if it's selected or not
            fprintf(f5, "%s %s\n", contact.ph_list_poi[no_of_contacts].ph_no, contact.ph_list_poi[no_of_contacts].comment);
        printf("Number deleted successfully\n");
        fclose(f5);
    }
    if (ch == 'M' || ch == 'm')
    {
        printf("Options:");
        printf("--------------------------------\n");
        printf("Enter 'x' or 'X' to modify name.\nEnter 'y' or 'Y' to modify number\nEnter 'z' or 'Z' to modify comment\n");
        printf("--------------------------------\nEnter your choice:");
        scanf(" %c", &ans);
        if (ans == 'y' || ans == 'Y')
        {
            /*Asking user to enter the S.No of ph_no and changing in the array pointed by array in the structure 
			at that index by taking modified no. as input from user.
			*/
            printf("Enter the S.No of the no. you want to modify:");
            scanf(" %d", &mod);
            if (mod <= no_of_contacts)
            {
                printf("Enter modified no:");
                scanf(" %s", contact.ph_list_poi[mod - 1].ph_no);
            }
            else
            {
                printf("\nPlease enter the correct S.No fom the above provided details.");
                return;
            }
        }
        if (ans == 'z' || ans == 'Z')
        {
            /*Asking user to enter the S.No of comment and changing in the array pointed by array in the structure 
			at that index by taking modified comment as input from user.
			*/
            printf("Enter the S.No of the no. you want to modify:");
            scanf(" %d", &mod);
            if (mod <= no_of_contacts)
            {
                printf("Enter modified comment:");
                scanf(" %[^\n]", contact.ph_list_poi[mod - 1].comment);
            }
            else
            {
                printf("\nNumber exceeded the no. of contacts");
                return;
            }
        }
        if (ans == 'x' || ans == 'X')
        {
            //asking the modified name and changing in the structure.
            printf("Enter modified name:");
            scanf(" %[^\n]", contact.name);
        }
        //finally appending the details in the structure to the file.
        f6 = fopen("phdir.txt", "a"); //closed at line 312.
        fprintf(f6, "%s\t%d ", contact.name, no_of_contacts);
        for (int j = 0; (j < no_of_contacts - 1); j++)
        {
            fprintf(f6, "%s %s\t", contact.ph_list_poi[j].ph_no, contact.ph_list_poi[j].comment);
        }
        fprintf(f6, "%s %s\n", contact.ph_list_poi[no_of_contacts - 1].ph_no, contact.ph_list_poi[no_of_contacts - 1].comment);
        printf("Contact modified successfully\n");
        fclose(f6);
    }
    free(contact.ph_list_poi); //freeing the memory allocated for the pointer in structure variable.
}
void clear()
{
    FILE *f = fopen("phdir.txt", "w"); //opening the directory in write mode to clear whole content.
    fclose(f);
}
int main()
{
    char c;
    int ret;
    char dum;
    printf("Welcome to your phone's directory!\n");
    printf("========================================================\n");
    printf("Enter a command(S-for Search,A-Add,M-Modify,C-Clear directory,Q-Quit):");
    c = getchar();
    while (c != 'Q')
    { //Adding
        if (c == 'A' || c == 'a')
        {
            ret = add();
            if (ret == 1)
                printf("Contact added successfully\n");
        }
        if (c == 'S' || c == 's')
            search(); //Searching
        if (c == 'M' || c == 'm')
        { //Modifying
            modify();
        }
        if (c == 'C' || c == 'c')
        { //Clearing
            clear();
            printf("Cleared Successfully!\n");
        }
        printf("======================================================\n");
        printf("Enter a command(S-for Search,A-Add,M-Modify,C-Clear directory,Q-Quit):");
        scanf(" %c", &c);
    }
    if (c == 'Q' || c == 'q')
    {
        printf("Bye!\n");
        exit;
    }
}
