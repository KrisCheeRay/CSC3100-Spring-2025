// #include <iostream>
// #include <vector>
// #include <stack>
// #include <algorithm>

// using namespace std;

// struct Product {
//     long long perf, rel, sat;
//     Product(long long p, long long r) : perf(p), rel(r), sat(p + r) {}
// };

// struct Request {
//     long long min_perf, min_rel;
//     int idx;
//     Request(long long p, long long r, int i) : min_perf(p), min_rel(r), idx(i) {}
// };

// bool cmp_product(const Product& a, const Product& b) { return a.perf > b.perf; }
// bool cmp_request(const Request& a, const Request& b) { return a.min_perf > b.min_perf; }

// vector<long long> max_satisfaction(int n, int m, vector<long long>& perf, vector<long long>& rel, vector<pair<long long, long long>>& reqs) {
//     vector<Product> products;
//     for (int i = 0; i < n; i++) products.emplace_back(perf[i], rel[i]);
//     sort(products.begin(), products.end(), cmp_product);
//     vector<Request> requests;
//     for (int i = 0; i < m; i++) requests.emplace_back(reqs[i].first, reqs[i].second, i);
//     sort(requests.begin(), requests.end(), cmp_request);
//     stack<pair<long long, long long>> mono_stack;
//     vector<long long> answers(m);
//     int j = 0;
//     for (int i = 0; i < m; i++) {
//         while (j < n && products[j].perf >= requests[i].min_perf) {
//             long long r = products[j].rel;
//             long long s = products[j].sat;
//             while (!mono_stack.empty() && mono_stack.top().second <= s) mono_stack.pop();
//             mono_stack.push({r, s});
//             j++;
//         }
//         long long max_sat = -1;
//         stack<pair<long long, long long>> temp = mono_stack;
//         while (!temp.empty()) {
//             if (temp.top().first >= requests[i].min_rel) max_sat = max(max_sat, temp.top().second);
//             temp.pop();
//         }
//         answers[requests[i].idx] = max_sat;
//     }
//     return answers;
// }

// int main() {
//     int n, m;
//     cin >> n >> m;
//     vector<long long> perf(n);
//     vector<long long> rel(n);
//     for (int i = 0; i < n; i++) cin >> perf[i];
//     for (int i = 0; i < n; i++) cin >> rel[i];
//     vector<pair<long long, long long>> reqs(m);
//     for (int i = 0; i < m; i++) cin >> reqs[i].first >> reqs[i].second;
//     vector<long long> result = max_satisfaction(n, m, perf, rel, reqs);
//     for (int i = 0; i < m; i++) {
//         cout << result[i];
//         if (i < m - 1) cout << " ";
//     }
//     cout << endl;
//     return 0;
// }

// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// struct Product {
//     long long perf, rel, sat;
//     Product(long long p, long long r) : perf(p), rel(r), sat(p + r) {}
// };

// struct Request {
//     long long min_perf, min_rel;
//     int idx;
//     Request(long long p, long long r, int i) : min_perf(p), min_rel(r), idx(i) {}
// };

// bool cmp_product(const Product& a, const Product& b) { return a.perf > b.perf; }
// bool cmp_request(const Request& a, const Request& b) { return a.min_perf > b.min_perf; }

// vector<long long> max_satisfaction(int n, int m, vector<long long>& perf, vector<long long>& rel, vector<pair<long long, long long>>& reqs) {
//     vector<Product> products;
//     for (int i = 0; i < n; i++) products.emplace_back(perf[i], rel[i]);
//     sort(products.begin(), products.end(), cmp_product);
    
//     vector<Request> requests;
//     for (int i = 0; i < m; i++) requests.emplace_back(reqs[i].first, reqs[i].second, i);
//     sort(requests.begin(), requests.end(), cmp_request);

//     vector<long long> answers(m, -1);
//     int j = 0;
//     vector<pair<long long, long long>> valid_products;

//     for (int i = 0; i < m; i++) {
//         // Insert products into valid_products while satisfying min_perf condition
//         while (j < n && products[j].perf >= requests[i].min_perf) {
//             long long r = products[j].rel;
//             long long s = products[j].sat;
//             // Keep only products with increasing satisfaction in valid_products
//             while (!valid_products.empty() && valid_products.back().second <= s) {
//                 valid_products.pop_back();
//             }
//             valid_products.push_back({r, s});
//             j++;
//         }

//         // Find the best product that satisfies min_rel condition
//         long long max_sat = -1;
//         for (const auto& product : valid_products) {
//             if (product.first >= requests[i].min_rel) {
//                 max_sat = max(max_sat, product.second);
//             }
//         }

//         answers[requests[i].idx] = max_sat;
//     }

//     return answers;
// }

// int main() {
//     int n, m;
//     cin >> n >> m;
//     vector<long long> perf(n);
//     vector<long long> rel(n);
//     for (int i = 0; i < n; i++) cin >> perf[i];
//     for (int i = 0; i < n; i++) cin >> rel[i];
//     vector<pair<long long, long long>> reqs(m);
//     for (int i = 0; i < m; i++) cin >> reqs[i].first >> reqs[i].second;

//     vector<long long> result = max_satisfaction(n, m, perf, rel, reqs);
//     for (int i = 0; i < m; i++) {
//         cout << result[i];
//         if (i < m - 1) cout << " ";
//     }
//     cout << endl;
//     return 0;
// }


import java.util.*;

public class Main {

    static class Product {
        long perf, rel, sat;
        Product(long p, long r) {
            this.perf = p;
            this.rel = r;
            this.sat = p + r;
        }
    }

    static class Request {
        long min_perf, min_rel;
        int idx;
        Request(long p, long r, int i) {
            this.min_perf = p;
            this.min_rel = r;
            this.idx = i;
        }
    }

    public static List<Long> maxSatisfaction(int n, int m, List<Long> perf, List<Long> rel, List<Pair<Long, Long>> reqs) {
        List<Product> products = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            products.add(new Product(perf.get(i), rel.get(i)));
        }

        products.sort((a, b) -> Long.compare(b.perf, a.perf));

        List<Request> requests = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            requests.add(new Request(reqs.get(i).first, reqs.get(i).second, i));
        }

        requests.sort((a, b) -> Long.compare(b.min_perf, a.min_perf));

        List<Long> answers = new ArrayList<>(Collections.nCopies(m, -1L));
        int j = 0;
        List<Pair<Long, Long>> validProducts = new ArrayList<>();

        for (Request req : requests) {
            while (j < n && products.get(j).perf >= req.min_perf) {
                Product product = products.get(j);
                long r = product.rel;
                long s = product.sat;

                while (!validProducts.isEmpty() && validProducts.get(validProducts.size() - 1).second <= s) {
                    validProducts.remove(validProducts.size() - 1);
                }
                validProducts.add(new Pair<>(r, s));
                j++;
            }

            long maxSat = -1;
            for (Pair<Long, Long> product : validProducts) {
                if (product.first >= req.min_rel) {
                    maxSat = Math.max(maxSat, product.second);
                }
            }

            answers.set(req.idx, maxSat);
        }

        return answers;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int m = sc.nextInt();
        List<Long> perf = new ArrayList<>();
        List<Long> rel = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            perf.add(sc.nextLong());
        }
        for (int i = 0; i < n; i++) {
            rel.add(sc.nextLong());
        }
        List<Pair<Long, Long>> reqs = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            reqs.add(new Pair<>(sc.nextLong(), sc.nextLong()));
        }

        List<Long> result = maxSatisfaction(n, m, perf, rel, reqs);
        for (int i = 0; i < m; i++) {
            System.out.print(result.get(i));
            if (i < m - 1) System.out.print(" ");
        }
        System.out.println();
    }

    static class Pair<T, U> {
        T first;
        U second;
        Pair(T first, U second) {
            this.first = first;
            this.second = second;
        }
    }
}
