#pragma once
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

using std::vector;

namespace decoder {

    namespace wheel {

        template<class T>
        struct Node {
            T value;
            struct Node<T>* parent;
            vector< struct Node<T> >* children;
        };

        struct Attributes {
            bool isStart;
            bool isEnd;
            int idRangeStart;
            int idRangeStop;
        };

        template<class T>
        struct OriginNode {
            vector< struct Node<T>* > children;
        };

        template<class T>
        struct ResultNode {
            T value;
            struct Attributes* attr;
        };

        template<class T>
        struct FinalNode {
            struct ResultNode<T>* result;
            struct Node<T>* parent;
        };

        template<class T>
        struct Layer {
            vector< struct Node<T>* > nodes;
        };
    }

}
