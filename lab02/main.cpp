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

    bool operator==(SparseVector& other) const {
        if (this->dimension != other.dimension) return false;

        Node* currentLeft = this->head;
        Node* currentRight = other.head;

        while(currentLeft && currentRight) {
            if (currentLeft->index != currentRight->index) return false;
            if (currentLeft->value != currentRight->value) return false;

            currentLeft = currentLeft->next;
            currentRight = currentRight->next;
        }

        return currentLeft == nullptr && currentRight == nullptr;
    }

    bool operator!=(SparseVector& other) const {
        return !(*this == other);
    }

    SparseVector operator+(const SparseVector& other) const {
        if (this->dimension != other.dimension) {
            throw invalid_argument("Vectors must have the same dimensions");
        }

        SparseVector newVector = SparseVector(this->dimension);

        for (int i = 0; i < this->dimension; i++) {
            double value = (*this)[i] + other[i];
            newVector.Append(i, value);
        }

        return newVector;
    }

    SparseVector operator-(const SparseVector& other) const {
        if (this->dimension != other.dimension) {
            throw invalid_argument("Vectors must have the same dimensions");
        }

        SparseVector newVector = SparseVector(this->dimension);

        for (int i = 0; i < this->dimension; i++) {
            double value = (*this)[i] - other[i];
            newVector.Append(i, value);
        }

        return newVector;
    }

    SparseVector operator*(const double scalar) const {
        SparseVector newVector = SparseVector(this->dimension);

        for (int i = 0; i < this->dimension; i++) {
            double value = (*this)[i] * scalar;
            newVector.Append(i, value);
        }

        return newVector;
    }

    operator double*() const {
        double* arr = new double[this->dimension]{};
        Node* current = this->head;
        while(current) {
            arr[current->index] = current->value;
            current = current->next;
        }
        return arr;
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

    double Dot(const SparseVector& other) const {
        if (this->dimension != other.dimension) {
            throw invalid_argument("Vectors must have the same dimensions");
        }

        double dotProduct = 0.0;

        Node* current = this->head;
        while(current) {
            dotProduct += current->value * other[current->index];
            current = current->next;
        }

        return dotProduct;
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
    cout << "=== Creating vectors ===" << endl;
    double* arr1 = new double[5]{1.0, 0.0, 0.0, 2.0, 0.0};
    double* arr2 = new double[5]{0.0, 3.0, 0.0, 2.0, 5.0};

    SparseVector v1(5, arr1);
    SparseVector v2(5, arr2);

    cout << "v1 = " << v1;
    cout << "v2 = " << v2;

    cout << "\n=== Copy constructor ===" << endl;
    SparseVector v3 = v1;
    cout << "v3 (copy of v1) = " << v3;

    cout << "\n=== operator[] ===" << endl;
    cout << "v1[0] = " << v1[0] << endl;
    cout << "v1[3] = " << v1[3] << endl;

    cout << "\n=== Arithmetic ===" << endl;
    cout << "v1 + v2 = " << (v1 + v2);
    cout << "v1 - v2 = " << (v1 - v2);
    cout << "v1 * 2.0 = " << (v1 * 2.0);

    cout << "\n=== Dot product ===" << endl;
    cout << "v1 . v2 = " << v1.Dot(v2) << endl;

    cout << "\n=== Comparison ===" << endl;
    cout << "v1 == v2: " << ((v1 == v2) ? "Yes" : "No") << endl;
    cout << "v1 != v2: " << ((v1 != v2) ? "Yes" : "No") << endl;
    cout << "v1 == v3: " << ((v1 == v3) ? "Yes" : "No") << endl;

    cout << "\n=== Type conversion to double* ===" << endl;
    double* arr3 = (double*)v1;
    for (int i = 0; i < 5; i++) {
        cout << arr3[i] << " ";
    }
    cout << endl;

    cout << "\n=== Move assignment ===" << endl;
    SparseVector v4 = SparseVector(5, arr1);
    cout << "v4 (moved from v1) = " << v4;

    cout << "\n=== Input ===" << endl;
    SparseVector v5(5);
    cin >> v5;
    cout << "v5 = " << v5;

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    return 0;
}
