#pragma once

#include <unordered_map>
#include <string>
#include <math>

/**
 * @file  weight.h
 * @brief Weighting schemes
*/

namespace SearchRPI {
class BM25 {
    public:
        BM25(const std::unordered_map<std::string, int>& doc_freqs, int total_docs, double k1 = 1.5, double b = 0.75);

        /**
         * @brief Compute BM25 score for a document
         * @param term_freqs Map of term frequencies in the document
         * @param doc_length Length of the document
         * @param avg_doc_length Average document length in corpus
         * @return BM25 score
        */
        double computeScore(const std::unordered_map<std::string, int>& term_freqs, int doc_length, double avg_doc_length);
    
    private:
        int N; //total number of documents
        double k1, b;
        std::unordered_map<std::string, double> idf; //stores precomputed idf for documents
        void computeIDF(const std::unordered_map<std::string, int>& doc_freqs); 
};
}