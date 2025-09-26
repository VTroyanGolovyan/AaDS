#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

template <typename T>
class PersistantStack {
private:
    struct Node {
        T value;
        Node* child;

        explicit Node(const T& value) : value(value), child(nullptr) {}
    };

    struct VersionInfo {
        size_t size;
        Node* top;
    };

public:
    using version_t = unsigned int;

    PersistantStack() {
        versions_.push_back({0, nullptr});
    }

    // deep copy!!!!
    PersistantStack(const PersistantStack& other); // todo
    PersistantStack& operator=(const PersistantStack& other); // todo

    PersistantStack(PersistantStack&& other); // todo
    PersistantStack& operator=(PersistantStack&& other); // todo

    ~PersistantStack() {
        clearAllVersions();
    }

    void clearAllVersions() {
        std::vector<Node*> nodes;

        nodes.reserve(versions_.size());
        std::transform(
            versions_.begin(), 
            versions_.end(), 
            std::back_inserter(nodes), 
            [](const auto& info) {
                return info.top;
        });

        std::sort(nodes.begin(), nodes.end());
        auto it = std::unique(nodes.begin(), nodes.end());

        nodes.erase(it, nodes.end());

        for (auto* node : nodes) {
            delete node;
        }
    }

    version_t push(version_t v, const T& value) {
        assert(v < versions_.size());

        Node* new_node = new Node(value);
        new_node->child = versions_[v].top;
        size_t new_size = versions_[v].size + 1;

        versions_.push_back({new_size, new_node});

        return versions_.size() - 1;
    }

    version_t pop(version_t v) {
        assert(v < versions_.size());
        assert(versions_[v].top != nullptr);

        Node* new_top = versions_[v].top->child;
        size_t new_size = versions_[v].size - 1;

        versions_.push_back({new_size, new_top});

        return versions_.size() - 1;
    }
    
    const T& top(version_t v) const {
        assert(v < versions_.size());
        assert(versions_[v].top != nullptr);

        return versions_[v].top->value;
    }

    size_t size(version_t v) const {
        assert(v < versions_.size());
    }

    bool empty(version_t v) const {
        assert(v < versions_.size());
        return size(v) == 0;
    }

private:
    std::vector<VersionInfo> versions_;

};


int main()
{
    PersistantStack<int> st;

    int v1 = st.push(0, 1);
    int v2 = st.push(v1, 1);

    int v3 = st.push(v2, 2);
    int v4 = st.pop(v3);

    for (PersistantStack<int>::version_t v : {v1, v2, v3, v4}) {
        std::cout << "Version " << v << " top " << st.top(v) << "\n";
    }
    
}
