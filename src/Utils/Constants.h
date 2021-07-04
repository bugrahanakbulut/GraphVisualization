using namespace sf;

class Constants
{
    public:
        constexpr static const int ADJACENCY_DISTANCE_THRESHOLD = 100;
        constexpr static const float ADJACENCY_POSSIBLITY_AFTER_EXCEED_THRESHOLD = 0.25F;
        constexpr static const float ADJACENCY_POSSIBLITY = 1;
        constexpr static const float DEFAULT_ADD_ADJACENCY = 1;

        constexpr static const float NODE_RADIUS = 10;
        constexpr static const float NODE_INDEX_CHAR_SIZE = 15;


        static Color GET_NODE_COLOR()
        {
            return Color::Blue;
        }

        static Color GET_NODE_INDEX_TEXT_COLOR()
        {
            return Color::White;
        }

        static Color GET_EDGE_COLOR()
        {
            return Color::Blue;
        }
};


