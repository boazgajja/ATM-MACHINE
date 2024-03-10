#include<stdio.h>
#include<windows.h>
#include<unistd.h>
#include<time.h>
#include<conio.h>

struct Customer {
    char name[10];
    char phone[15];
    int transaction;
    int total_amount;
    int id;
    int password;
    int count;
};

void generate_pin(struct Customer[], int, int);
void block_card(struct Customer[], int, int);
void deposit_amount(struct Customer[], int, int);
void withdraw_amount(struct Customer[], int, int);
void check_balance(struct Customer[], int, int);
void transfer_money(struct Customer[], int, int);
void print_customer(struct Customer[], int);
int security_check(struct Customer[], int, int);
int block_account(struct Customer[], int, int);
void update_file(struct Customer[], int);
void check_attempts(struct Customer[], int, int, int);
void welcome_message();

int main(){
	int user_choice, num_customers, i, attempt_count = 0, master_password, entered_password, machine_password, counter = 0;
	struct Customer customers[10];
	FILE *file_pointer;
	
	file_pointer = fopen("customer_info.txt", "r");
	fscanf(file_pointer, "%d", &num_customers);
	fscanf(file_pointer, "%d", &master_password);
	
	for(i = 2; i < 16; i++) { 
		fscanf(file_pointer, "%d%d%s%d%s", &customers[i].id, &customers[i].password, 
			   customers[i].phone, &customers[i].total_amount, customers[i].name);
	}
	fclose(file_pointer);
	
	int menu_choice;
	char entered_id[10];
	welcome_message();
	printf("ENTER ID:");
	scanf("%s", entered_id);
	printf("ENTER PASSWORD:");
	scanf("%d", &entered_password);
	
	if(entered_password == master_password) {
		system("cls");
		welcome_message();
		printf("LOGIN SUCCESSFUL\n");
		sleep(1);
		system("cls");
		welcome_message();
		while(1) {
			print_customer(customers, num_customers);
			printf("1 TO GENERATE PIN\n");
			printf("2 TO BLOCK ATM CARD\n");
			printf("3 TO DEPOSIT AMOUNT\n");
			printf("4 TO WITHDRAW AMOUNT\n");
			printf("5 TO CHECK YOUR BANK BALANCE\n");
			printf("6 TO TRANSFER MONEY TO OTHER ACCOUNT\n");
			printf("ENTER NUMBER: ");
			scanf("%d", &menu_choice);
			switch(menu_choice) {
				case 1:
					generate_pin(customers, num_customers, counter);
					system("cls");
					welcome_message();
					break;
				case 2:
					block_card(customers, num_customers, counter);
					system("cls");
					welcome_message();
					break;
				case 3:
					deposit_amount(customers, num_customers, counter);
					system("cls");
					welcome_message();
					break;
				case 4:
					withdraw_amount(customers, num_customers, counter);
					system("cls");
					welcome_message();
					break;
				case 5:
					check_balance(customers, num_customers, counter);
					system("cls");
					welcome_message();
					break;
				case 6:
					transfer_money(customers, num_customers, counter);
					system("cls");
					welcome_message();
					break;
				default:
					system("cls");
					welcome_message();
					printf("ENTER 1 TO FILL MONEY IN ATM MACHINE\n");
					printf("ENTER 2 TO TURN OFF THIS MACHINE\n");
					scanf("%d", &menu_choice);
					if(menu_choice == 1) {
						printf("ENTER YOUR PASSWORD:");
						scanf("%d", &machine_password);
						if(machine_password == entered_password) {
							printf("MACHINE IS OPENED, FILL THE AMOUNT\a\n");
							printf("PRESS ANY KEY TO CONTINUE");
							getch();
							system("cls");
							welcome_message();
							continue;
						} else {
							system("cls");
							welcome_message();
							continue;
						}	
					} else if(menu_choice == 2) {
						printf("ENTER YOUR PASSWORD:");
						scanf("%d", &machine_password);
						if(machine_password == entered_password) {
							printf("LOGGED OUT SUCCESSFULLY\n");
							printf("PRESS ANY KEY TO CONTINUE");
							getch();
							system("cls");
							welcome_message();
							break;
						} else {
							system("cls");
							welcome_message();
							continue;
						}	
					}
			}	
		}
	} else {
		printf("INVALID ID OR PASSWORD");
	}
	return 0;
}

void print_customer(struct Customer customers[], int i) {
    // Function implementation
}

void generate_pin(struct Customer customers[], int num_customers, int counter) {
    system("cls");
    welcome_message();
    int customer_id, index;
    printf("ENTER YOUR CUSTOMER ID: ");
    scanf("%d", &customer_id);
    
    // Find the index of the customer
    for (index = 2; index < num_customers; index++) {
        if (customers[index].id == customer_id) {
            break;
        }
    }
    
    if (index == num_customers) {
        printf("CUSTOMER NOT FOUND\n");
        printf("PRESS ANY KEY TO CONTINUE\n");
        getch();
        return;
    }
    char num[15];
    printf("ENTER YOUR PHONE NUMBER ACCORDING TO BANK");
    scanf("%s",num);
    for(int i=0;i<10;i++){
        if(num[i]!=customers[index].phone[i]){
            printf("ENTERED INVALID PHONE NUMBER");
            generate_pin(customers,num_customers,counter);
        }
    }

    int new_pin, confirm_pin;
    printf("ENTER YOUR NEW FOUR DIGIT PIN: ");
    scanf("%d", &new_pin);
    printf("CONFIRM YOUR PIN: ");
    scanf("%d", &confirm_pin);
    
    if (new_pin == confirm_pin) {
        customers[index].password = new_pin;
        printf("PROCESSING...\n");
        sleep(1);
        printf("PIN CREATED SUCCESSFULLY\n");
        printf("THANK YOU\n");
        printf("PRESS ANY KEY TO CONTINUE\n");
        getch();
        update_file(customers, num_customers);
    } else {
        printf("TWO PINS ARE DIFFERENT\nPLEASE TRY AGAIN\n");
        printf("PRESS ANY KEY TO CONTINUE\n");
        getch();
        generate_pin(customers, num_customers, counter);
    }
}

void block_card(struct Customer customers[], int num_customers, int m) {
    // Function implementation
}

void deposit_amount(struct Customer customers[], int num_customers, int m) {
    // Function implementation
}

void withdraw_amount(struct Customer customers[], int num_customers, int m) {
    // Function implementation
}

void check_balance(struct Customer customers[], int num_customers, int m) {
    // Function implementation
}

void transfer_money(struct Customer customers[], int num_customers, int m) {
    // Function implementation
}

int security_check(struct Customer customers[], int num_customers, int m) {
    // Function implementation
}

int block_account(struct Customer customers[], int i, int num_customers) {
    // Function implementation
}

void update_file(struct Customer customers[], int num_customers) {
    FILE *file_pointer;
    file_pointer = fopen("customer_info.txt", "w");
    
    fprintf(file_pointer, "%d\n", num_customers);
    fprintf(file_pointer, "%d\n", customers[1].password); // Master password
    
    for (int i = 2; i < num_customers; i++) {
        fprintf(file_pointer, "%d %d %s %d %s\n", customers[i].id, customers[i].password,
                customers[i].phone, customers[i].total_amount, customers[i].name);
    }
    
    fclose(file_pointer);
}

void check_attempts(struct Customer customers[], int m, int i, int num_customers) {
    // Function implementation
}

void welcome_message() {
   int i;
    time_t t;
    time(&t);
    for (i = 2; i < 121; i++) {
        printf("#");
    }
    printf("\t\t\t\t\tWELCOME TO XYZ ATM MACHINE\t\t\t\t%s", ctime(&t));
    
    for (i = 2; i < 122; i++) {
        printf("#");
    }
    printf("\t\t\t\t\t\t\t\t IF ANY PROBLEM OCCURRED IN THIS MACHINE CALL: 9987543264\n");
}

