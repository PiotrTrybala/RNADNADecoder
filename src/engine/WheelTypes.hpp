#pragma once
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

using std::vector;

namespace Decoder {

    namespace Wheel {

        template<class T>
        struct Node {
            T value;
            struct Node<T> parent;
            vector< struct Node<T> > children;
        };

        struct Attributes {};

        template<class T>
        struct OriginNode {
            vector< struct Node<T> > children;
        };

        template<class T>
        struct ResultNode {
            T value;
            struct Attributes* attr;
            vector<struct Node<T> > parents;
        };

        template<class T>
        struct FinalNode {
            struct ResultNode<T> result;
            struct Node<T> parent;
        };
    }

}
