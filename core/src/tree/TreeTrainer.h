#ifndef GRADIENTFOREST_TREETRAINER_H
#define GRADIENTFOREST_TREETRAINER_H

#include "PredictionStrategy.h"
#include "RelabelingStrategy.h"
#include "SplittingRuleFactory.h"
#include "Data.h"
#include "Tree.h"
#include "TreeOptions.h"
#include "BootstrapSampler.h"

class TreeTrainer {
public:
  TreeTrainer(RelabelingStrategy *relabeling_strategy,
              SplittingRuleFactory *splitting_rule_factory,
              PredictionStrategy *prediction_strategy,
              TreeOptions *options);

  Tree* train(Data *data,
              BootstrapSampler *bootstrap_sampler,
              Observations* observations);

private:
  void createEmptyNode(std::vector <std::vector<size_t>> &child_nodeIDs,
                       std::vector <std::vector<size_t>> &sampleIDs,
                       std::vector <size_t> &split_varIDs,
                       std::vector<double> &split_values);

  void createPossibleSplitVarSubset(std::vector<size_t> &result,
                                    BootstrapSampler *bootstrap_sampler,
                                    Data *data,
                                    const std::vector<double> &split_select_weights);

  bool splitNode(size_t nodeID,
                 SplittingRule *splitting_rule,
                 BootstrapSampler *bootstrap_sampler,
                 Data *data,
                 Observations *observations,
                 std::vector <std::vector<size_t>> &child_nodeIDs,
                 std::vector <std::vector<size_t>> &sampleIDs,
                 std::vector <size_t> &split_varIDs,
                 std::vector<double> &split_values,
                 const std::vector<double> &split_select_weights);

  bool splitNodeInternal(size_t nodeID,
                         SplittingRule *splitting_rule,
                         Observations* observations,
                         const std::vector <size_t> &possible_split_varIDs,
                         std::vector <std::vector<size_t>> &sampleIDs,
                         std::vector <size_t> &split_varIDs,
                         std::vector<double> &split_values);

  RelabelingStrategy *relabeling_strategy;
  SplittingRuleFactory *splitting_rule_factory;
  PredictionStrategy *prediction_strategy;
  TreeOptions* options;
};

#endif //GRADIENTFOREST_TREETRAINER_H