#include "main.h"


void push(Node **head, char new_firstname[20], char new_secondname[20], char new_otchestvo[20], char new_age[5], char new_phone_number[12], char new_work_place[20], char new_work_post[20], char new_media[50]) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    strncpy(tmp->firstname, new_firstname, 20);
    strncpy(tmp->secondname, new_secondname, 20);
    strncpy(tmp->otchestvo, new_otchestvo, 20);
    strncpy(tmp->phone_number, new_phone_number, 12);
    strncpy(tmp->work_place, new_work_place, 20);
    strncpy(tmp->work_post, new_work_post, 20);
    strncpy(tmp->media, new_media, 50);
    strncpy(tmp->age, new_age, 5);
    tmp->next = (*head);
    tmp->primary_key = (*head)->primary_key + 1;
    (*head) = tmp;
}


Node* find_person(Node *head, int primary_key) {
    Node *ptr = head;
    int flag_person_fined = 0;
    while(ptr != NULL && !flag_person_fined) {
        if (ptr->primary_key == primary_key) {
            flag_person_fined = 1;
        } else {
            ptr = ptr->next;
        }
   }
   return ptr;
}


Node* find_prev_person(Node *head, int primary_key) {
    Node *ptr = head;
    Node *prev = NULL;
    int flag_person_fined = 0;
    while(ptr != NULL && !flag_person_fined) {
        if (ptr->primary_key == primary_key) {
            flag_person_fined = 1;
        } else {
            prev = ptr;
            ptr = ptr->next;
        }
   }
   return prev;
}


void delete_from_structure(Node **head, int primary_key) {
    Node *prev = find_prev_person( *head, primary_key);
    if (prev->next != NULL) {
        Node *elm  = prev->next;
        if (elm->next != NULL) {
            prev->next = elm->next;
            free(elm);   
        } else {
            printf("Такого элемента не существует\n");
        }
    } else {
        printf("Такого элемента не существует\n");
    }
}


void pop(Node **head) {
    Node* prev = NULL;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    (*head) = (*head)->next;
    free(prev);
}


void menu(Node **head){
    int choice_temp_var = 0;
    printf("\n1. Добавить запись в книгу.\n2. Удалить запись из книги.\n3. Посмотреть телефонную книгу.\n4. Изменение записи.\n");
    printf("Выберите опцию для работы: ");
    scanf("%d", &choice_temp_var);
    switch (choice_temp_var)
    {
    case 1:
        printf("Выбрано добавление\n");
        add_person_choice(head);
        break;
    case 2:
        printf("Выбрано удаление\n");
        delete_person_choice(head);
        break;
    case 3:
        printf("Выбран просмотр\n");
        printList(*head);
        break;
    case 4:
        printf("Выбрано изменение:\n");
        change_person(head);
        break;
    default:
        printf("Выбран неверный пункт меню\n");
        break;
    }
}


void printList(Node *head) {
   Node *ptr = head;
   printf("\n[ ");

   //начать с начала
   while(ptr != NULL) {
    if (ptr->primary_key != 0) {
        printf("\n%d \n",ptr->primary_key);
        printf("%s \n",ptr->firstname);
        printf("%s \n",ptr->secondname);
        printf("%s \n",ptr->otchestvo);
        printf("%s \n",ptr->phone_number);
        printf("%s \n",ptr->work_place);
        printf("%s \n",ptr->work_post);
        printf("%s \n",ptr->media);
        printf("%s \n",ptr->age);
    }
        ptr = ptr->next;
   }
   printf(" ]");
}


void delete_person_choice(Node **head) {
    int selected_primary_key = 0;
    printf("\nВведите индекс контакта, который хотите удалить: ");
    scanf("%d", &selected_primary_key);

    if ((*head)->next == NULL){
        printf("\nКнига пуста, невозможно удалить\n");
    } else if ((*head)->primary_key == selected_primary_key) {
        pop(head);
    } else {
        delete_from_structure(head, selected_primary_key);
    }
}


void add_person_choice(Node **head) {
    int flag_exit_add = 1;
    int menu_choice = -1;
    char new_firstname[20] = "";
    char new_secondname[20] = "";
    char new_otchestvo[20] = "";
    char new_age[5]= "";
    char new_phone_number[12] = "";
    char new_work_place[20] = "";
    char new_work_post[20] = "";
    char new_media[50] = "";
    while (flag_exit_add) {
        printf("\n 0. Закончить заполнение.\n 1. Имя. \n 2. Фамилию. \n 3. Отчество. \n 4. Возраст.\n 5. Номер телефона.\n 6. Место работы.\n 7. Соц сети.\nВведите, какое поле необходимо заполнить: ");
        scanf("%d", &menu_choice);
        switch (menu_choice)
        {
        case 0:
            flag_exit_add = 0;
            break;
        case 1:
            printf("Введите имя: ");
            scanf("%s", new_firstname);
            break;
        case 2:
            printf("Введите фамилию: ");
            scanf("%s", new_secondname);
            break;
        case 3:
            printf("Введите отчество: ");
            scanf("%s", new_otchestvo);
            break;
        case 4:
            printf("Введите возраст: ");
            scanf("%s", new_age);
            break;
        case 5:
            printf("Введите номер телефона: ");
            scanf("%s", new_phone_number);
            break;
        case 6:
            printf("Введите место работы: ");
            scanf("%s", new_work_place);
            break;
        case 7:
            printf("Введите должность: ");
            scanf("%s", new_work_post);
            break;
        case 8:
            printf("Введите соц сети через пробел: ");
            scanf("%s", new_media);
            break;
        default:
            printf("Выбран неверный пункт меню\n");
            break;
        }
    }
    push(head, new_firstname, new_secondname, new_otchestvo, new_age, new_phone_number, new_work_place, new_work_post, new_media);
}

void change_person(Node **head) {
    Node *ptr = (*head);
    int index_person = 1;
    int flag_exit_add = 1;
    int menu_choice = -1;
    char new_firstname[20] = "";
    char new_secondname[20] = "";
    char new_otchestvo[20] = "";
    char new_age[5]= "";
    char new_phone_number[12] = "";
    char new_work_place[20] = "";
    char new_work_post[20] = "";
    char new_media[50] = "";
    printf("Для выхода наберите 0.\nВведите индекс записи, которую нужно изменить: ");
    scanf("%d", &index_person);
    while (flag_exit_add) {
        if (index_person!=0) {
            ptr = find_person(*head, index_person);
            printf("\n 0. Закончить изменение.\n 1. Имя. \n 2. Фамилию. \n 3. Отчество. \n 4. Возраст.\n 5. Номер телефона.\n 6. Место работы.\n 7. Соц сети.\nВведите, какое поле необходимо изменить: ");
            scanf("%d", &menu_choice);
            switch (menu_choice)
            {
            case 0:
                flag_exit_add = 0;
                break;
            case 1:
                printf("Старая запись: %s\n", ptr->firstname);
                printf("Введите имя: ");
                scanf("%s", new_firstname);
                strncpy(ptr->firstname, new_firstname, 20);
                break;
            case 2:
                printf("Старая запись: %s\n", ptr->secondname);
                printf("Введите фамилию: ");
                scanf("%s", new_secondname);
                strncpy(ptr->secondname, new_secondname, 20);
                break;
            case 3:
                printf("Старая запись: %s\n", ptr->otchestvo);
                printf("Введите отчество: ");
                scanf("%s", new_otchestvo);
                strncpy(ptr->otchestvo, new_otchestvo, 20);
                break;
            case 4:
                printf("Старая запись: %s\n", ptr->age);
                printf("Введите возраст: ");
                scanf("%s", new_age);
                strncpy(ptr->age, new_age, 5);
                break;
            case 5:
                printf("Старая запись: %s\n", ptr->phone_number);
                printf("Введите номер телефона: ");
                scanf("%s", new_phone_number);
                strncpy(ptr->phone_number, new_phone_number, 12);
                break;
            case 6:
                printf("Старая запись: %s\n", ptr->work_place);
                printf("Введите место работы: ");
                scanf("%s", new_work_place);
                strncpy(ptr->work_place, new_work_place, 20);
                break;
            case 7:
                printf("Старая запись: %s\n", ptr->work_post);
                printf("Введите должность: ");
                scanf("%s", new_work_post);
                 strncpy(ptr->work_post, new_work_post, 20);
                break;
            case 8:
                printf("Старая запись: %s\n", ptr->media);
                printf("Введите соц сети через пробел: ");
                scanf("%s", new_media);
                strncpy(ptr->media, new_media, 50);
                break;
            default:
                printf("Выбран неверный пункт меню\n");
                break;
            }
        }
    }
}


void struct_init(Node *head) {
    head->primary_key = 0;
    strncpy(head->firstname, "", 1);
    strncpy(head->secondname, "", 1);
    strncpy(head->otchestvo, "", 1);
    strncpy(head->age, "", 1);
    strncpy(head->phone_number, "", 1);
    strncpy(head->work_place, "", 1);
    strncpy(head->work_post, "", 1);
    strncpy(head->media, "", 1);
}


// void start_screen() {

//     printf("\ \        / / | |                          | |  "
//         " \ \  /\  / /__| | ___ ___  _ __ ___   ___  | |_ ___    "
//         "  \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \   "
//         "   \  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |  "
//         " ___\/  \/ \___|_|\___\___/|_| |_|_|_|\___|  \__\___/   "
//         "|  __ \| |                      |  _ \            | |   "
//         "| |__) | |__   ___  _ __   ___  | |_) | ___   ___ | | __"
//         "|  ___/| '_ \ / _ \| '_ \ / _ \ |  _ < / _ \ / _ \| |/ / "
//         "| |    | | | | (_) | | | |  __/ | |_) | (_) | (_) |   < "
//         "|_|    |_| |_|\___/|_| |_|\___| |____/ \___/ \___/|_|\_\"  );
// }


int main() {
    Node *phone_book_head = (Node*) calloc(sizeof(Node), 1);
    struct_init(phone_book_head);
    while (1) {
        menu(&phone_book_head);
    }
    return 0;
}


