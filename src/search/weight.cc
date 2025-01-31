#include "weight.h"

namespace SearchRPI {

BM25::BM25(const std::unordered_map<std::string, int>& doc_freqs, int total_docs, double k1 = 1.5, double b = 0.75) {
    N = total_docs;
    k1 = k1;
    b = b;

    computeIDF(doc_freqs);
}

double BM25::computeScore(const std::unordered_map<std::string, int>& term_freqs, int doc_length, double avg_doc_length) {
    double score = 0.0;

    for (const auto& [term, df] : term_freqs){
        if (idf[term] == idf.end()){
            continue;
        }

        double tf_component = (freq * (k1 + 1.0)) / (freq + k1 * (1 - b + b * (doc_length / avg_doc_length)));

        score += idf[term] * tf_component;
    }

    return score;
}


void BM25::computeIDF(const std::unordered_map<std::string, int>& doc_freqs) {
    for (const auto& [term, df] : doc_freqs){
        idf[term] = std::log((N - df + 0.5)/(df + 0.5) + 1.0);
    }
}

}