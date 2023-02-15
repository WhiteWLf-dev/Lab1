#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
class Lab1 {
	struct Elements {
	std::string date;
	size_t win;
	size_t number;
	size_t cost;
    friend bool operator== (const Elements& c1, const Elements& c2) {
        if (c1.date == c2.date) {
            if (c1.win == c2.win) {
                if (c1.number == c1.number) {
                    return true;
                }
            }
        }
        return false;
    }
    friend bool operator >(const Elements& c1, const Elements& c2) {
        if (std::strcmp(c1.date.c_str(), c2.date.c_str()) == -1) {
            return false;
        }
        if (std::strcmp(c1.date.c_str(), c2.date.c_str()) == 1) {
            return true;
        }
        if (std::strcmp(c1.date.c_str(), c2.date.c_str()) == 0) {
            if (c1.win < c2.win) {
                return true;
            }
            if (c1.win > c2.win) {
                return false;
            }
            if (c1.win == c2.win) {
                if (c1.number > c2.number) {
                    return true;
                }
                if (c1.number < c2.number) {
                    return false;
                }
                if (c1.number == c2.number) {
                    return false;
                }
            }
        }
    }
    };
    friend bool operator <(const Elements& c1, const Elements& c2) {
        if (c1 == c2) {
            return false;
        }
        return !(c1 > c2);
    }
    friend bool operator >=(const Elements& c1, const Elements& c2) {
        if (c1 == c2) {
            return true;
        }
        return c1 > c2;
        
    }
    friend bool operator <=(const Elements& c1, const Elements& c2) {
        if (c1==c2) {
            return true;
        }
        return c1 < c2;
    }
    
	std::vector<Lab1::Elements> data;
    
public:
    std::string filename;
    Lab1() = default;
	Lab1(std::string namefile);
    void bubbleSort();
    void selectionSort();
    void heapify(size_t n, size_t i);
    void heapSort();
    void output();
    ~Lab1() = default;
};
Lab1::Lab1(std::string namefile)
{
    std::ifstream inf(namefile);
    filename = namefile;

    if (!inf.is_open())
    {
        std::cerr << "The file could not be opened for reading!\n";
    }
    std::string s;
    while (std::getline(inf, s)) { 
        Lab1::Elements obj;
        size_t i = 0;
        bool flag = 1;
        std::string num;
        while (flag) {
            if (s[i] == ' ') {
                flag = 0;
                i++;
                break;
            }
            else {
                num += s[i];
                i++;
            }
        }
        obj.number = std::stoi(num.c_str());
        std::string cost;
        flag = 1;
        while (flag) {
            if (s[i] == ' ') {
                flag = 0;
                i++;
                break;
            }
            else {
                cost += s[i];
                i++;
            }
        }
        obj.cost = std::stoi(cost.c_str());
        std::string date;
        flag = 1;
        while (flag) {
            if (s[i] == ' ') {
                flag = 0;
                i++;
                break;
            }
            else {
                date += s[i];
                i++;
            }
        }
        obj.date = date;
        flag = 1;
        std::string sum;
        while (flag) {
            if (i==s.size()) {
                flag = 0;
                break;
            }
            else {
                sum += s[i];
                i++;
            }
        }
        
        obj.win = std::stoi(sum.c_str());
        data.push_back(obj);
    }
    inf.close();
}
void Lab1::bubbleSort()
{
    size_t len = data.size();
    while (len--)
    {
        bool swapped = false;

        for (size_t i = 0; i < len; i++)
        {
            if (data[i] > data[i + 1])
            {
                std::swap(data[i], data[i + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
}
void Lab1::selectionSort() {
    size_t i, j, min_idx;
    for (i = 0; i < data.size() - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < data.size(); j++)
        {
            if (data[j] < data[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            std::swap(data[min_idx], data[i]);
    }
}
void Lab1::heapify(size_t n,size_t i) {

    size_t largest = i;
    size_t l = 2 * i + 1; 
    size_t r = 2 * i + 2; 

    if (l < n && data[l] > data[largest])
        largest = l;

    if (r < n && data[r] > data[largest])
        largest = r;
    if (largest != i)
    {
        std::swap(data[i], data[largest]);
        heapify( n, largest);
    }
}
void Lab1::heapSort() {

    for (int i = data.size() / 2 - 1; i >= 0; i--) {
        heapify(data.size(), i);
    }
    for (int i = data.size() - 1; i >= 0; i--)
    {
        std::swap(data[0], data[i]);
        heapify(i, 0);
    }
}
void Lab1::output()
{
    std::ofstream out;        
    out.open("SORTED MODE"+filename);
    if (out.is_open())
    {
        for (auto& it : data) {
            out << it.number << " " << it.cost << " " << it.date << " " << it.win << "\n";
        }
    }
}
int main() {
    std::string p = "100.txt";
    Lab1 v(p);
    v.filename = "heapSort"+v.filename;
    auto begin = std::chrono::steady_clock::now();
    v.heapSort();
    auto end = std::chrono::steady_clock::now();
    v.output();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time heapSort 100: " << elapsed_ms.count() << " ms\n";
    p = "1000.txt";
    Lab1 v1(p);
    v1.filename = "heapSort" + v1.filename;
    begin = std::chrono::steady_clock::now();
    v1.heapSort();
    end = std::chrono::steady_clock::now();
    v1.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time heapSort 1000: " << elapsed_ms.count() << " ms\n";
    p = "5000.txt";
    Lab1 v2(p);
    v2.filename = "heapSort" + v2.filename;
    begin = std::chrono::steady_clock::now();
    v2.heapSort();
    end = std::chrono::steady_clock::now();
    v2.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time heapSort 5000: " << elapsed_ms.count() << " ms\n";
    p = "10000.txt";
    Lab1 v3(p);
    v3.filename = "heapSort" + v3.filename;
    begin = std::chrono::steady_clock::now();
    v3.heapSort();
    end = std::chrono::steady_clock::now();
    v3.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time heapSort 10000: " << elapsed_ms.count() << " ms\n";
    p = "20000.txt";
    Lab1 v4(p);
    v4.filename = "heapSort" + v4.filename;
    begin = std::chrono::steady_clock::now();
    v4.heapSort();
    end = std::chrono::steady_clock::now();
    v4.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time heapSort 20000: " << elapsed_ms.count() << " ms\n";
    p = "40000.txt";
    Lab1 v5(p);
    v5.filename = "heapSort" + v5.filename;
    begin = std::chrono::steady_clock::now();
    v5.heapSort();
    end = std::chrono::steady_clock::now();
    v5.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time heapSort 40000: " << elapsed_ms.count() << " ms\n";
    p = "100000.txt";
    Lab1 v6(p);
    v6.filename = "heapSort" + v6.filename;
    begin = std::chrono::steady_clock::now();
    v6.heapSort();
    end = std::chrono::steady_clock::now();
    v6.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time heapSort 100000: " << elapsed_ms.count() << " ms\n";
    
    std::cout << "\n";
    p = "100.txt";
    Lab1 h(p);
    h.filename = "bubbleSort" + h.filename;
    begin = std::chrono::steady_clock::now();
    h.bubbleSort();
    end = std::chrono::steady_clock::now();
    h.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time bubbleSort 100: " << elapsed_ms.count() << " ms\n";
    p = "1000.txt";
    Lab1 h1(p);
    h1.filename = "bubbleSort" + h1.filename;
    begin = std::chrono::steady_clock::now();
    h1.bubbleSort();
    end = std::chrono::steady_clock::now();
    h1.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time bubbleSort 1000: " << elapsed_ms.count() << " ms\n";
    p = "5000.txt";
    Lab1 h2(p);
    h2.filename = "bubbleSort" + h2.filename;
    begin = std::chrono::steady_clock::now();
    h2.bubbleSort();
    end = std::chrono::steady_clock::now();
    h2.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time bubbleSort 5000: " << elapsed_ms.count() << " ms\n";
    p = "10000.txt";
    Lab1 h3(p);
    h3.filename = "bubbleSort" + h3.filename;
    begin = std::chrono::steady_clock::now();
    h3.bubbleSort();
    end = std::chrono::steady_clock::now();
    h3.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time bubbleSort 10000: " << elapsed_ms.count() << " ms\n";
    p = "20000.txt";
    Lab1 h4(p);
    h4.filename = "bubbleSort" + h4.filename;
    begin = std::chrono::steady_clock::now();
    h4.bubbleSort();
    end = std::chrono::steady_clock::now();
    h4.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time bubbleSort 20000: " << elapsed_ms.count() << " ms\n";
    p = "40000.txt";
    Lab1 h5(p);
    h5.filename = "bubbleSort" + h5.filename;
    begin = std::chrono::steady_clock::now();
    h5.bubbleSort();
    end = std::chrono::steady_clock::now();
    h5.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time bubbleSort 40000: " << elapsed_ms.count() << " ms\n";
    p = "100000.txt";
    Lab1 h6(p);
    h6.filename = "bubbleSort" + h6.filename;
    begin = std::chrono::steady_clock::now();
    h6.bubbleSort();
    end = std::chrono::steady_clock::now();
    h6.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time bubbleSort 100000: " << elapsed_ms.count() << " ms\n";

    std::cout << "\n";
    p = "100.txt";
    Lab1 k(p);
    k.filename = "selSort" + k.filename;
    begin = std::chrono::steady_clock::now();
    k.selectionSort();
    end = std::chrono::steady_clock::now();
    k.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time selSort 100: " << elapsed_ms.count() << " ms\n";
    p = "1000.txt";
    Lab1 k1(p);
    k1.filename = "selSort" + k1.filename;
    begin = std::chrono::steady_clock::now();
    k1.selectionSort();
    end = std::chrono::steady_clock::now();
    k1.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time selSort 1000: " << elapsed_ms.count() << " ms\n";
    p = "5000.txt";
    Lab1 k2(p);
    k2.filename = "selSort" + k2.filename;
    begin = std::chrono::steady_clock::now();
    k2.selectionSort();
    end = std::chrono::steady_clock::now();
    k2.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time selSort 5000: " << elapsed_ms.count() << " ms\n";
    p = "10000.txt";
    Lab1 k3(p);
    k3.filename = "selSort" + k3.filename;
    begin = std::chrono::steady_clock::now();
    k3.selectionSort();
    end = std::chrono::steady_clock::now();
    k3.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time selSort 10000: " << elapsed_ms.count() << " ms\n";
    p = "20000.txt";
    Lab1 k4(p);
    k4.filename = "selSort" + k4.filename;
    begin = std::chrono::steady_clock::now();
    k4.selectionSort();
    end = std::chrono::steady_clock::now();
    k4.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time selSort 20000: " << elapsed_ms.count() << " ms\n";
    p = "40000.txt";
    Lab1 k5(p);
    k5.filename = "selSort" + k5.filename;
    begin = std::chrono::steady_clock::now();
    k5.selectionSort();
    end = std::chrono::steady_clock::now();
    k5.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time selSort 40000: " << elapsed_ms.count() << " ms\n";
    p = "100000.txt";
    Lab1 k6(p);
    k6.filename = "selSort" + k6.filename;
    begin = std::chrono::steady_clock::now();
    k6.selectionSort();
    end = std::chrono::steady_clock::now();
    k6.output();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time selSort 100000: " << elapsed_ms.count() << " ms\n";
}

