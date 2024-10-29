#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cfloat>

struct Coordinate {
    float x;
    float y;
    int coord_id;
    Coordinate *next;
    Coordinate *previous;
};

static int current_id = 0;

void add_coordinate(Coordinate **list_end, float x, float y);
void forward_display(Coordinate *list_start);
void backward_display(Coordinate *list_end);
void delete_coordinate(Coordinate **list_start, int coord_id_to_delete);
int list_length(Coordinate *list_start);
void closest_to(Coordinate *list_start, float x, float y);
void generate_random_coordinates(Coordinate **list_end, int num_coords);



int main(int argc, char *argv[]) {

    srand(static_cast<unsigned int>(time(0)));
    int num_coords = std::atoi(argv[1]);

    Coordinate *list_start = nullptr;
    Coordinate *list_end = nullptr;

    generate_random_coordinates(&list_end, num_coords);
    list_start = list_end;
    while (list_start && list_start->previous) {
        list_start = list_start->previous;
    }

    std::cout << "Forward Display:\n";
    forward_display(list_start);

    std::cout << "\nBackward Display:\n";
    backward_display(list_end);

    int delete_id = 2;  //ID to delete
    std::cout << "\nDeleting coordinate with ID " << delete_id << "\n";
    delete_coordinate(&list_start, delete_id);

    std::cout << "\nUpdated Forward Display:\n";
    forward_display(list_start);

    float find_x = 50.0f, find_y = 50.0f;
    std::cout << "\nFinding closest coordinate to (" << find_x << ", " << find_y << "):\n";
    closest_to(list_start, find_x, find_y);

    std::cout << "\nList length: " << list_length(list_start) << "\n";

    return 0;
}

void add_coordinate(Coordinate **list_end, float x, float y) {
    Coordinate *new_coord = new Coordinate;
    new_coord->x = x;
    new_coord->y = y;
    new_coord->coord_id = current_id++;
    new_coord->next = nullptr;
    new_coord->previous = *list_end;

    if (*list_end != nullptr) {
        (*list_end)->next = new_coord;
    }
    *list_end = new_coord;
}

void forward_display(Coordinate *list_start) {
    Coordinate *temp = list_start;
    while (temp) {
        std::cout << "ID: " << (temp->coord_id)+1 << " (x, y): (" << temp->x << ", " << temp->y << ")\n";
        temp = temp->next;
    }
}

void backward_display(Coordinate *list_end) {
    Coordinate *temp = list_end;
    while (temp) {
        std::cout << "ID: " << (temp->coord_id)+1 << " (x, y): (" << temp->x << ", " << temp->y << ")\n";
        temp = temp->previous;
    }
}

void delete_coordinate(Coordinate **list_start, int coord_id_to_delete) {
    Coordinate *temp = *list_start;
    while (temp && temp->coord_id != coord_id_to_delete) {
        temp = temp->next;
    }
    if (temp) {
        if (temp->previous) {
            temp->previous->next = temp->next;
        } else {
            *list_start = temp->next;
        }
        if (temp->next) {
            temp->next->previous = temp->previous;
        }
        delete temp;
        std::cout << "Coordinate ID " << coord_id_to_delete << " deleted.\n";
    } else {
        std::cout << "Coordinate ID not found.\n";
    }
}

int list_length(Coordinate *list_start) {
    int count = 0;
    Coordinate *temp = list_start;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

void closest_to(Coordinate *list_start, float x, float y) {
    Coordinate *temp = list_start;
    Coordinate *closest = nullptr;
    float min_distance = FLT_MAX;

    while (temp) {
        float distance = std::sqrt((temp->x - x) * (temp->x - x) + (temp->y - y) * (temp->y - y));
        if (distance < min_distance) {
            min_distance = distance;
            closest = temp;
        }
        temp = temp->next;
    }

    if (closest) {
        std::cout << "Closest to (" << x << ", " << y << "): ID " << closest->coord_id
                  << " at (" << closest->x << ", " << closest->y << ") with distance " << min_distance << "\n";
    }
}

void generate_random_coordinates(Coordinate **list_end, int num_coords) {
    for (int i = 0; i < num_coords; ++i) {
        float x = static_cast<float>(rand() % 100);
        float y = static_cast<float>(rand() % 100);
        add_coordinate(list_end, x, y);
    }
}
