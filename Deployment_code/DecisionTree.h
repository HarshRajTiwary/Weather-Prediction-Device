#pragma once
// #include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTree {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[1] <= 79.95000076293945) {
                            if (x[1] <= 50.0) {
                                return 3;
                            }

                            else {
                                return 2;
                            }
                        }

                        else {
                            if (x[0] <= 24.049999237060547) {
                                return 0;
                            }

                            else {
                                return 1;
                            }
                        }
                    }

                protected:
                };
            }
        }
    }