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
        
        FILE *file_pointer;
        
        file_pointer = fopen("customer_info.txt", "r");
        fscanf(file_pointer, "%d", &num_customers);
        fscanf(file_pointer, "%d", &master_password);
        struct Customer customers[num_customers+3];
        for(i = 2; i < 16; i++) { 
            fscanf(file_pointer, "%d%d%s%d%s", &customers[i].id, &customers[i].password, 
                customers[i].phone, &customers[i].total_amount, customers[i].name);
        }
        customers[1].password=master_password;
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
    void print_customer(struct Customer o[], int i) {
        printf("%d%d%s%d%s", o[i].id, o[i].password, o[i].phone, o[i].total_amount, o[i].name);
    }

    void generate_pin(struct Customer customers[], int num_customers, int attempts) {
        system("cls");
        welcome_message();
        int i, new_pin, confirm_pin, option;
        i = security_check(customers, num_customers, attempts);
        if (i == 0) {
            printf("YOUR ACCOUNT HAS BEEN BLOCKED \n");
            printf("PLEASE CONTACT THE BANK FOR DETAILS\n");
            printf("PRESS ANY KEY TO CONTINUE");
            getch();
            return;
        } else if (i == 1) {
            printf("ACCOUNT NOT FOUND\n");
            printf("PLEASE CONTACT THE BANK\n");
            printf("ENTER 1 TO RETURN HOME\n");
            printf("ENTER 2 TO CONTINUE\n");
            scanf("%d", &option);
            if (option == 1)
                return ;
            else
                generate_pin(customers, num_customers, attempts);
        } else {
            printf("ENTER YOUR NEW FOUR DIGIT PIN: ");
            scanf("%d", &new_pin);
            printf("ENTER THE FOUR DIGIT PIN AGAIN FOR CONFIRMATION: ");
            scanf("%d", &confirm_pin);
            if (new_pin == confirm_pin) {
                customers[i].password = new_pin;
                update_file(customers, num_customers);
                printf("PROCESSING......\n");
                sleep(1);
                printf("PIN CREATED SUCCESSFULLY\n");
                printf("THANK YOU\n");
                printf("PRESS ANY KEY TO CONTINUE");
                getch();
            } else {
                printf("THE TWO PINS ARE DIFFERENT\nPLEASE TRY AGAIN\n");
                printf("PRESS ANY KEY TO CONTINUE\n");
                getch();
                generate_pin(customers, num_customers, attempts);
            }
        }
    }

    void block_card(struct Customer customers[], int num_customers, int attempts) {
        system("cls");
        welcome_message();
        int i, option;
        i = security_check(customers, num_customers, attempts);
        if (i == 0) {
            printf("YOUR ACCOUNT HAS BEEN BLOCKED \n");
            printf("PLEASE CONTACT THE BANK FOR DETAILS\n");
            printf("PRESS ANY KEY TO CONTINUE");
            getch();
        } else if (i == 1) {
            printf("ACCOUNT NOT FOUND\n");
            printf("PLEASE CONTACT THE BANK\n");
            printf("ENTER 1 TO RETURN HOME\n");
            printf("ENTER 2 TO CONTINUE\n");
            scanf("%d", &option);
            if (option == 1)
                return ;
            else
                generate_pin(customers, num_customers, attempts);
        } else {
            customers[i].password = 0000;
            update_file(customers, num_customers);
            printf("PROCESSING.......\n");
            sleep(2);
            printf("YOUR ACCOUNT IS BLOCKED \n");
            sleep(2);
        }
    }

    void deposit_amount(struct Customer customers[], int num_customers, int attempts) {
        system("cls");
        welcome_message();
        int i, amount, option;
        i = security_check(customers, num_customers, attempts);
        if (i == 0) {
            printf("YOUR ACCOUNT HAS BEEN BLOCKED \n");
            printf("PLEASE CONTACT THE BANK FOR DETAILS\n");
            printf("PRESS ANY KEY TO CONTINUE");
            getch();
        } else if (i == 1) {
            printf("ACCOUNT NOT FOUND\n");
            printf("PLEASE CONTACT THE BANK\n");
            printf("ENTER 1 TO RETURN HOME\n");
            printf("ENTER 2 TO CONTINUE\n");
            scanf("%d", &option);
            if (option == 1)
                return ;
            else
                generate_pin(customers, num_customers, attempts);
        } else {
            printf("ENTER THE AMOUNT: ");
            scanf("%d", &amount);
            customers[i].total_amount += amount;
            printf("TRANSACTION COMPLETED\n\a");
            printf("CHECK YOUR BALANCE\n");
            printf("PRESS ANY KEY TO CONTINUE\n");
            printf("THANK YOU");
            getch();
            update_file(customers, num_customers);
        }
    }

    void withdraw_amount(struct Customer customers[], int num_customers, int attempts) {
        system("cls");
        welcome_message();
        int i, amount, option;
        i = security_check(customers, num_customers, attempts);
        if (i == 0) {
            printf("YOUR ACCOUNT HAS BEEN BLOCKED \n");
            printf("PLEASE CONTACT THE BANK FOR DETAILS\n");
            printf("PRESS ANY KEY TO CONTINUE");
            getch();
        } else if (i == 1) {
            printf("ACCOUNT NOT FOUND\n");
            printf("PLEASE CONTACT THE BANK\n");
            printf("ENTER 1 TO RETURN HOME\n");
            printf("ENTER 2 TO CONTINUE\n");
            scanf("%d", &option);
            if (option == 1)
                return ;
            else
                generate_pin(customers, num_customers, attempts);
        } else {
            printf("ENTER THE AMOUNT: ");
            scanf("%d", &amount);
            if (amount < customers[i].total_amount) {
                customers[i].total_amount -= amount;
                printf("TRANSACTION COMPLETED \nCOLLECT THE AMOUNT\a\n");
                printf("CHECK THE BALANCE\n");
                printf("PRESS ANY KEY TO CONTINUE\n");
                printf("THANK YOU");
                getch();
                update_file(customers, num_customers);
            } else {
                printf("YOU HAVE INSUFFICIENT BALANCE\n");
            }
        }
    }

    void check_balance(struct Customer customers[], int num_customers, int attempts) {
        system("cls");
        welcome_message();
        int i, option;
        i = security_check(customers, num_customers, attempts);
        if (i == 0) {
            printf("YOUR ACCOUNT HAS BEEN BLOCKED \n");
            printf("PLEASE CONTACT THE BANK FOR DETAILS\n");
            printf("PRESS ANY KEY TO CONTINUE");
            getch();
        } else if (i == 1) {
            printf("ACCOUNT NOT FOUND\n");
            printf("PLEASE CONTACT THE BANK\n");
            printf("ENTER 1 TO RETURN HOME\n");
            printf("ENTER 2 TO CONTINUE\n");
            scanf("%d", &option);
            if (option == 1)
                return ;
            else
                generate_pin(customers, num_customers, attempts);
        } else {
            printf("YOUR ACCOUNT BALANCE: %d\n", customers[i].total_amount);
        }
    }

    void transfer_money(struct Customer customers[], int num_customers, int attempts) {
        system("cls");
        welcome_message();
        int i, j, option, receiver_id, trans_amount;
        i = security_check(customers, num_customers, attempts);
        if (i == 0) {
            printf("YOUR ACCOUNT HAS BEEN BLOCKED \n");
            printf("PLEASE CONTACT THE BANK FOR DETAILS\n");
            printf("PRESS ANY KEY TO CONTINUE");
            getch();
        } else if (i == 1) {
            printf("ACCOUNT NOT FOUND\n");
            printf("PLEASE CONTACT THE BANK\n");
            printf("ENTER 1 TO RETURN HOME\n");
            printf("ENTER 2 TO CONTINUE\n");
            scanf("%d", &option);
            if (option == 1)
                return ;
            else
                generate_pin(customers, num_customers, attempts);
        } else {
            printf("\nEnter the amount you want to transfer\n");
            scanf("%d", &trans_amount);
            if (customers[i].total_amount < trans_amount) {
                printf("You have insufficient balance\n");
            } else {
                printf("Details of money receiving account\n");
                scanf("%d", &receiver_id);
                for (j = 2; j < num_customers; j++) {
                    if (customers[j].id == receiver_id)
                        break;
                }
                if (j == num_customers) {
                    printf("Account not found\n");
                    printf("Enter 1 to return home\n");
                    printf("Enter 2 to continue\n");
                    scanf("%d", &option);
                    if (option == 1)
                        return;
                    else
                        transfer_money(customers, num_customers, attempts);
                } else {
                    customers[i].total_amount -= trans_amount;
                    customers[j].total_amount += trans_amount;
                    printf("Money Transferred\n");
                    printf("THANK YOU");
                    printf("PRESS ANY KEY TO CONTINUE\n");
                    getch();
                    update_file(customers, num_customers);
                }
            }
        }
    }

    int security_check(struct Customer customers[], int num_customers, int attempts) {
        system("cls");
        welcome_message();
        int i, login_id, login_pin;
        check_attempts(customers, attempts, i, num_customers);
        printf("ENTER YOUR ACCOUNT NUMBER: ");
        scanf("%d", &login_id);
        for (i = 2; i < num_customers; i++) {
            if (customers[i].id == login_id)
                break;
        }
        if (i == num_customers)
            return 1;
        else {
            printf("ENTER YOUR PIN: ");
            scanf("%d", &login_pin);
            if (login_pin == customers[i].password)
                return i;
            else if (customers[i].password == 0)
                return 0;    
            else {
                printf("INCORRECT PIN. PLEASE TRY AGAIN....\n");
                attempts++;
                printf("PRESS ANY KEY TO CONTINUE");
                getch();
                security_check(customers, num_customers, attempts);
            }
        }
    }

    int block_account(struct Customer customers[], int i, int num_customers) {
        customers[i].password= 0000;
        update_file(customers, num_customers);
        printf("PROCESSING.......\n");
        sleep(2);
        printf("YOUR ACCOUNT IS BLOCKED \n");
        sleep(2);
        return 1;
    }

    void update_file(struct Customer customers[], int num_customers) {
        int i;
        FILE *file_ptr;
        file_ptr = fopen("myfile.txt", "w");
        fprintf(file_ptr, "%d\n", num_customers);
        fprintf(file_ptr, "%d\n",customers[1].password);
        for (i = 2; i < num_customers; i++) {
            fprintf(file_ptr, "%d %d %s %d %s\n", customers[i].id, customers[i].password, customers[i].phone, customers[i].total_amount, customers[i].name);
        }
        fclose(file_ptr);
    }

    void check_attempts(struct Customer customers[], int attempts, int i, int num_customers) {
        printf("%d", attempts);
        if (attempts == 3) {
            block_account(customers, i, num_customers);
            printf("DUE TO MULTIPLE ATTEMPTS\nPLEASE CONTACT THE BANK\n");
            printf("THANK YOU");
            printf("PRESS ANY KEY TO CONTINUE");
            getch();
        }
    }
    void welcome_message() {
    int i;
        time_t t;
        time(&t);
        for (i = 2; i < 130; i++) {
            printf("#");
        }
        printf("                    WELCOME TO XYZ ATM MACHINE\t\t\t\t%s", ctime(&t));
        
        for (i = 2; i < 130; i++) {
            printf("#");
        }
        printf("                          IF ANY PROBLEM OCCURRED IN THIS MACHINE CALL: 9987543264\n");
    }

