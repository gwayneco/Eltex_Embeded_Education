#include "main.h"

Contact
fill_structure(struct Contact person, int new_primary_key,
               char new_firstname[SIZE_STR], char new_secondname[SIZE_STR],
               char new_otchestvo[SIZE_STR], char new_phone_number[SIZE_STR],
               char new_work_place[SIZE_STR], char new_work_post[SIZE_STR]) {
  person.primary_key = new_primary_key;
  strncpy(person.firstname, new_firstname, SIZE_STR);
  strncpy(person.secondname, new_secondname, SIZE_STR);
  strncpy(person.otchestvo, new_otchestvo, SIZE_STR);
  strncpy(person.phone_number, new_phone_number, SIZE_STR);
  strncpy(person.work_place, new_work_place, SIZE_STR);
  strncpy(person.work_post, new_work_post, SIZE_STR);
  return person;
}

void add_person_choice(
    tree_node **head, Contact *new_person) { // Если выбрано добавление контакта
  int new_primary_key = 0;
  int flag_exit_add = 1;
  int menu_choice = -1;
  char new_firstname[SIZE_STR] = "";
  char new_secondname[SIZE_STR] = "";
  char new_otchestvo[SIZE_STR] = "";
  char new_phone_number[SIZE_STR] = "";
  char new_work_place[SIZE_STR] = "";
  char new_work_post[SIZE_STR] = "";
  while (flag_exit_add) {
    printf(
        "----------------------------------------------------------------------"
        "----------------------\n"
        " 0. Закончить заполнение.\n 1. Ключ. \n 2. Имя. \n 3. Фамилию. \n 4. "
        "Отчество.\n 5. Номер телефона.\n 6. Место работы.\n 7. Должность.\n "
        "Введите, какое поле необходимо заполнить: ");
    scanf("%d", &menu_choice);
    switch (menu_choice) {
    case 0:
      flag_exit_add = 0;
      break;
    case 1:
      printf("Ключ для значения: ");
      scanf("%d", &new_primary_key);
      break;
    case 2:
      printf("Введите имя: ");
      scanf("%s", new_firstname);
      break;
    case 3:
      printf("Введите фамилию: ");
      scanf("%s", new_secondname);
      break;
    case 4:
      printf("Введите отчество: ");
      scanf("%s", new_otchestvo);
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
    default:
      printf("Выбран неверный пункт меню\n");
      break;
    }
  }
  *new_person = fill_structure(*new_person, new_primary_key, new_firstname,
                               new_secondname, new_otchestvo, new_phone_number,
                               new_work_place, new_work_post);
  insert_btree(*new_person, head);
}

void delete_person_choice(tree_node **head) {
  int selected_primary_key = 0;
  printf("\nВведите индекс контакта, который хотите удалить: ");
  scanf("%d", &selected_primary_key);
  delete_item_btree(selected_primary_key, head);
}

void change_person(tree_node **head) {
  tree_node *ptr = (*head);
  int index_person = 1;
  int flag_exit_add = 1;
  int menu_choice = -1;
  char new_firstname[SIZE_STR] = "";
  char new_secondname[SIZE_STR] = "";
  char new_otchestvo[SIZE_STR] = "";
  char new_phone_number[SIZE_STR] = "";
  char new_work_place[SIZE_STR] = "";
  char new_work_post[SIZE_STR] = "";
  printf("Для выхода наберите 0.\nВведите индекс записи, которую нужно "
         "изменить: ");
  scanf("%d", &index_person);
  while (flag_exit_add) {
    if (index_person != 0) {
      ptr = find_btree(*head, index_person);
      if (ptr == NULL) {
        printf("Элемента с таким индексом не существует\n");
        return;
      }
      printf(
          "\n 0. Закончить изменение.\n 1. Имя. \n 2. Фамилию. \n 3. Отчество. "
          "\n 4. Возраст.\n 5. Номер телефона.\n 6. Место работы.\n 7. Соц "
          "сети.\nВведите, какое поле необходимо изменить: ");
      scanf("%d", &menu_choice);
      switch (menu_choice) {
      case 0:
        flag_exit_add = 0;
        break;
      case 1:
        printf("Старая запись: %s\n", ptr->value.firstname);
        printf("Введите имя: ");
        scanf("%s", new_firstname);
        strncpy(ptr->value.firstname, new_firstname, SIZE_STR);
        break;
      case 2:
        printf("Старая запись: %s\n", ptr->value.secondname);
        printf("Введите фамилию: ");
        scanf("%s", new_secondname);
        strncpy(ptr->value.secondname, new_secondname, SIZE_STR);
        break;
      case 3:
        printf("Старая запись: %s\n", ptr->value.otchestvo);
        printf("Введите отчество: ");
        scanf("%s", new_otchestvo);
        strncpy(ptr->value.otchestvo, new_otchestvo, SIZE_STR);
        break;
      case 4:
        printf("Старая запись: %s\n", ptr->value.phone_number);
        printf("Введите номер телефона: ");
        scanf("%s", new_phone_number);
        strncpy(ptr->value.phone_number, new_phone_number, SIZE_STR);
        break;
      case 5:
        printf("Старая запись: %s\n", ptr->value.work_place);
        printf("Введите место работы: ");
        scanf("%s", new_work_place);
        strncpy(ptr->value.work_place, new_work_place, SIZE_STR);
        break;
      case 6:
        printf("Старая запись: %s\n", ptr->value.work_post);
        printf("Введите должность: ");
        scanf("%s", new_work_post);
        strncpy(ptr->value.work_post, new_work_post, SIZE_STR);
        break;
      default:
        printf("Выбран неверный пункт меню\n");
        break;
      }
    }
  }
}

void menu(tree_node **head) {
  int flag_exit = 1;
  Contact *new_person = (Contact *)malloc(sizeof(Contact));
  int choice_temp_var = 0;
  while (flag_exit) {
    printf("-------------------------------------------------------------------"
           "-------------------------"
           "\n1. Добавить запись в книгу.\n2. Удалить запись из книги.\n3. "
           "Посмотреть телефонную книгу.\n4. Изменение записи.\n5. Выход.\n"
           "-------------------------------------------------------------------"
           "-------------------------\n");

    printf("Выберите опцию для работы: ");
    scanf("%d", &choice_temp_var);
    switch (choice_temp_var) {
    case 1:
      printf("Выбрано добавление\n"
             "-----------------------------------------------------------------"
             "---------------------------\n");
      add_person_choice(head, new_person);
      break;
    case 2:
      printf("Выбрано удаление\n"
             "-----------------------------------------------------------------"
             "---------------------------\n");
      delete_person_choice(head);
      break;
    case 3:
      printf("Выбран просмотр\n"
             "-----------------------------------------------------------------"
             "---------------------------\n");
      print_btree(*head);
      break;
    case 4:
      printf("Выбрано изменение:\n"
             "-----------------------------------------------------------------"
             "---------------------------\n");
      change_person(head);
      break;
    case 5:
      printf("Выход из программы\n"
             "-----------------------------------------------------------------"
             "---------------------------\n");
      // delete_list(*head);
      flag_exit = 0;
      break;
    default:
      printf("Выбран неверный пункт меню\n"
             "-----------------------------------------------------------------"
             "---------------------------\n");
      break;
    }
  }
}

int main() {
  struct tree_node *head = NULL;
  menu(&head);
  return 0;
}
