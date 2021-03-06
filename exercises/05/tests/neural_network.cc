#include <doctest/doctest.h>

#include <neural_network.h>
#include <utils.h>

TEST_CASE("The neural network is default constructible.") {
  neural_network<sigmoid<float>> network{};
  CHECK(network.layer_count() == 1);
  CHECK(network.layer_size()[0] == 0);
}

TEST_CASE("The neural network is constructible through an initializer list.") {
  neural_network<sigmoid<float>> network{1, 2, 3};
  CHECK(network.layer_count() == 3);
  CHECK(network.layer_size()[0] == 1);
  CHECK(network.layer_size()[1] == 2);
  CHECK(network.layer_size()[2] == 3);

  network.weight(0, {1, 2});
  CHECK(network.weight(0)(0, 0) == 1);
  CHECK(network.weight(0)(1, 0) == 2);

  network.weight(1, {1, 2, 3, 4, 5, 6});
  CHECK(network.weight(1)(0, 0) == 1);
  CHECK(network.weight(1)(0, 1) == 2);
  CHECK(network.weight(1)(1, 0) == 3);
  CHECK(network.weight(1)(1, 1) == 4);
  CHECK(network.weight(1)(2, 0) == 5);
  CHECK(network.weight(1)(2, 1) == 6);

  network.bias(0, {1, 2});
  CHECK(network.bias(0)(0) == 1);
  CHECK(network.bias(0)(1) == 2);

  network.bias(1, {1, 2, 3});
  CHECK(network.bias(1)(0) == 1);
  CHECK(network.bias(1)(1) == 2);
  CHECK(network.bias(1)(2) == 3);
}

TEST_CASE("AND") {
  neural_network<sigmoid<float>> network{2, 3, 1};
  network.training_data(
      {{{0, 0}, {0}}, {{1, 0}, {0}}, {{0, 1}, {0}}, {{1, 1}, {1}}});

  CHECK(network.input(0)(0) == 0);
  CHECK(network.input(0)(1) == 0);
  CHECK(network.label(0)(0) == 0);

  CHECK(network.input(1)(0) == 1);
  CHECK(network.input(1)(1) == 0);
  CHECK(network.label(1)(0) == 0);

  CHECK(network.input(2)(0) == 0);
  CHECK(network.input(2)(1) == 1);
  CHECK(network.label(2)(0) == 0);

  CHECK(network.input(3)(0) == 1);
  CHECK(network.input(3)(1) == 1);
  CHECK(network.label(3)(0) == 1);

  network.train();
}

TEST_CASE("4.Exercise") {
  neural_network<sigmoid<float>> network{2, 2, 2};
  network.weight(0, {0.15, 0.20, 0.25, 0.30})
      .weight(1, {0.40, 0.45, 0.50, 0.55})
      .bias(0, {0.35, 0.35})
      .bias(1, {0.60, 0.60})
      .training_data({{{0.05, 0.10}, {0.01, 0.99}}})
      .learn_rate(0.5);
  MESSAGE("initial network:\n" << network);
  network.train();
  MESSAGE("network after training:\n" << network);
}

TEST_CASE("") {
  std::vector<int> data{1, 2, 3};
  neural_network<sigmoid<float>> network(data.begin(), data.end());
  CHECK(network.layer_count() == 3);
  CHECK(network.layer_size()[0] == 1);
  CHECK(network.layer_size()[1] == 2);
  CHECK(network.layer_size()[2] == 3);

  data = {1, 2};
  network.weight(0, data.begin(), data.end());
  CHECK(network.weight(0)(0, 0) == 1);
  CHECK(network.weight(0)(1, 0) == 2);

  data = {1, 2, 3, 4, 5, 6};
  network.weight(1, data.begin(), data.end());
  CHECK(network.weight(1)(0, 0) == 1);
  CHECK(network.weight(1)(0, 1) == 2);
  CHECK(network.weight(1)(1, 0) == 3);
  CHECK(network.weight(1)(1, 1) == 4);
  CHECK(network.weight(1)(2, 0) == 5);
  CHECK(network.weight(1)(2, 1) == 6);

  data = {1, 2};
  network.bias(0, data.begin(), data.end());
  CHECK(network.bias(0)(0) == 1);
  CHECK(network.bias(0)(1) == 2);

  data = {1, 2, 3};
  network.bias(1, data.begin(), data.end());
  CHECK(network.bias(1)(0) == 1);
  CHECK(network.bias(1)(1) == 2);
  CHECK(network.bias(1)(2) == 3);
}

TEST_CASE("") {
  std::vector<int> data{1, 2, 3};
  neural_network<sigmoid<float>> network(data);
  CHECK(network.layer_count() == 3);
  CHECK(network.layer_size()[0] == 1);
  CHECK(network.layer_size()[1] == 2);
  CHECK(network.layer_size()[2] == 3);

  data = {1, 2};
  network.weight(0, data);
  CHECK(network.weight(0)(0, 0) == 1);
  CHECK(network.weight(0)(1, 0) == 2);

  data = {1, 2, 3, 4, 5, 6};
  network.weight(1, data);
  CHECK(network.weight(1)(0, 0) == 1);
  CHECK(network.weight(1)(0, 1) == 2);
  CHECK(network.weight(1)(1, 0) == 3);
  CHECK(network.weight(1)(1, 1) == 4);
  CHECK(network.weight(1)(2, 0) == 5);
  CHECK(network.weight(1)(2, 1) == 6);

  data = {1, 2};
  network.bias(0, data);
  CHECK(network.bias(0)(0) == 1);
  CHECK(network.bias(0)(1) == 2);

  data = {1, 2, 3};
  network.bias(1, data);
  CHECK(network.bias(1)(0) == 1);
  CHECK(network.bias(1)(1) == 2);
  CHECK(network.bias(1)(2) == 3);
}

TEST_CASE("") {
  neural_network<sigmoid<float>> network(std::vector<int>{1, 2, 3});
  CHECK(network.layer_count() == 3);
  CHECK(network.layer_size()[0] == 1);
  CHECK(network.layer_size()[1] == 2);
  CHECK(network.layer_size()[2] == 3);
}