#include <iostream>

/* When using C++ templates, we can add template specializations
 * of existing template classes to extend their behavior without
 * actually touching the original templates.
 */

class UndirectedGraph {};
class DirectedGraph {};

template<typename Graph>
struct GraphAlgorithm {
    const Graph graph;

    void search() {
        std::cout << "Some search algorithm for graphs\n";
    }    
};

template<>
struct GraphAlgorithm <DirectedGraph> {
    const DirectedGraph graph;

    void search() {
        std::cout << "Some search algorithm only for directed graphs\n";
    }    
};

template<typename Graph>
void run(const Graph & graph) {
    GraphAlgorithm<Graph> algo{graph};
    algo.search();
}

int main()
{
    run(UndirectedGraph{});
    run(DirectedGraph{});
}
