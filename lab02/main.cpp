#include <iostream>

using namespace std;

class SparseVector {
private:
    struct Node {
        int index;
        double value;
        Node* next;

        Node(int index, double value) {
            this->index = index;
            this->value = value;
            this->next = nullptr;
        }
    };

    int dimension;
    Node* head;

public:
    SparseVector() {
        this->dimension = 0;
        this->head = nullptr;
    };

    SparseVector(int dimension) {
        this->dimension = dimension;
        this->head = nullptr;
    }

    SparseVector(int dimension, double* arr) {
        this->dimension = dimension;
        this->head = nullptr;

        for (int i = 0; i < dimension; i++) {
            this->Append(i, arr[i]);
        }
    }

    SparseVector(const SparseVector& other) {
        this->dimension = other.dimension;
        this->head = nullptr;

        Node* current = other.head;
        while(current) {
            this->Append(current->index, current->value);
            current = current->next;
        }
    }

    ~SparseVector() {
        this->Clear();
    };

    SparseVector& operator=(const SparseVector& other) {
        if (this == &other) return *this;

        this->Clear();
        this->dimension = other.dimension;
        Node* current = other.head;
        while(current) {
            this->Append(current->index, current->value);
            current = current->next;
        }

        return *this;
    }

    SparseVector& operator=(SparseVector&& other) {
        if (this == &other) return *this;

        this->Clear();
        this->dimension = other.dimension;
        this->head = other.head;

        other.head = nullptr;
        other.dimension = 0;
        return *this;
    }

    double operator[](int i) const {
        if (i < 0 || i >= this->dimension) {
            throw out_of_range("Index is out of range");
        }

        Node* current = this->head;
        while(current) {
            if (current->index == i) return current->value;
            current = current->next;
        }

        return 0.0;
    }

    friend ostream& operator<<(ostream& os, const SparseVector& v) {
        Node* current = v.head;
        os << "[";
        for (int i = 0; i < v.dimension; i++) {
            if (current != nullptr && current->index == i) {
                os << current->value;
                current = current->next;
            } else {
                os << 0;
            }

            if (i < v.dimension - 1) os << ", ";
        }
        os << "]" << endl;
        return os;
    }

    friend istream& operator>>(istream& is, SparseVector& v) {
        v.Clear();

        cout << "Enter " << v.dimension << "  coordinates: ";
        for (int i = 0; i < v.dimension; i++) {
            double value;
            is >> value;
            v.Append(i, value);
        }
        return is;
    }

private:
    void Append(int index, double value) {
        if (value == 0) return;

        Node* newNode = new Node(index, value);

        if (this->head == nullptr) {
            this->head = newNode;
            return;
        }

        Node* current = this->head;
        while(current->next) {
            current = current->next;
        }
        current->next = newNode;
        return;
    }

    void Clear() {
        while(head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    int dimension = 5;
    double* arr = new double[dimension]{1.0, 0.0, 0.0, 2.0, 0.0};

    SparseVector vector = SparseVector(dimension, arr);

    cout << vector;
    cin >> vector;
    cout << vector;
    cout << vector[0] << endl;

    delete[] arr;

    return 0;
}
