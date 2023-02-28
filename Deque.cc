#include <iostream>
#include <string>
const int massiveSize = 10;

class deque {
 private:
  int* front_;
  int* back_;
  int back_index_;
  int front_index_;
  int** massive_;
  int volume;
  void expand_deque();

 public:
  deque();
  void push_front(int num);
  void push_back(int num);
  void pop_front();
  void pop_back();
  void front();
  void back();
  void size();
  void clear();
  int exit();
  ~deque();
};

deque::deque() {
  volume = massiveSize;
  massive_ = new int* [massiveSize] { NULL };
  massive_[massiveSize / 2] = new int[massiveSize]{0};
  back_index_ = front_index_ = massiveSize / 2;
  front_ = back_ = nullptr;
};

deque::~deque() {
  for (int i = 0; i < volume; i++) {
    delete[] massive_[i];
    massive_[i] = nullptr;
  }
  delete[] massive_;
  front_ = back_ = nullptr;
  massive_ = nullptr;
};

void deque::push_front(int num) {
  if (!front_) {
    front_ = &massive_[volume / 2][massiveSize / 2 - 1];
    back_ = front_;
    *front_ = num;
    back_index_ = front_index_ = volume / 2;
  } else {
    if (front_ == &massive_[0][0]) {
      expand_deque();
      front_index_ += massiveSize / 2;
      back_index_ += massiveSize / 2;
    }
    if (front_ == &massive_[front_index_][0]) {
      front_index_--;
      massive_[front_index_] = new int[massiveSize];
      front_ = &massive_[front_index_][massiveSize - 1];
    } else {
      front_--;
    }
    *front_ = num;
  }
  std::cout << "ok" << std::endl;
}

void deque::push_back(int num) {
  if (!back_) {
    back_ = &massive_[volume / 2][massiveSize / 2];
    front_ = back_;
    *back_ = num;
    back_index_ = front_index_ = volume / 2;
  } else {
    if (back_ == &massive_[volume - 1][massiveSize - 1]) {
      expand_deque();
      back_index_ += massiveSize / 2;
      front_index_ += massiveSize / 2;
    }
    if (back_ == &massive_[back_index_][massiveSize - 1]) {
      back_index_++;
      massive_[back_index_] = new int[massiveSize];
      back_ = &massive_[back_index_][0];
    } else {
      back_++;
    }
    *back_ = num;
  }
  std::cout << "ok" << std::endl;
}

void deque::pop_front() {
  if (!front_) {
    std::cout << "error" << std::endl;
  } else if (front_ == back_) {
    std::cout << *front_ << std::endl;
    back_ = front_ = nullptr;
  } else {
    if (front_ == &massive_[front_index_][massiveSize - 1]) {
      front_index_++;
      std::cout << *front_ << std::endl;
      front_ = &massive_[front_index_][0];
    } else {
      std::cout << *front_ << std::endl;
      front_++;
    }
  }
}

void deque::pop_back() {
  if (!back_) {
    std::cout << "error" << std::endl;
  } else if (back_ == front_) {
    std::cout << *back_ << std::endl;
    back_ = front_ = nullptr;
  } else {
    if (back_ == &massive_[back_index_][0]) {
      back_index_--;
      std::cout << *back_ << std::endl;
      back_ = &massive_[back_index_][massiveSize - 1];
    } else {
      std::cout << *back_ << std::endl;
      back_--;
    }
  }
}

void deque::front() {
  !front_ ? std::cout << "error" : std::cout << *front_;
  std::cout << std::endl;
}

void deque::back() {
  !back_ ? std::cout << "error" : std::cout << *back_;
  std::cout << std::endl;
}

void deque::size() {
  int *tmp_back = back_, *tmp_front = front_;
  int tmp = 0;
  if (!back_ && !front_) {
    tmp_back = tmp_front = &massive_[back_index_][0];
  } else if (!back_ || !front_) {
    if (!back_) tmp_back = &massive_[volume / 2][volume / 2];
    if (!front_) tmp_front = &massive_[volume / 2][volume / 2 - 1];
  } else {
    tmp = 1;
  }
  std::cout << (back_index_ - front_index_) * volume +
                   ((tmp_back - &massive_[back_index_][0]) -
                    (tmp_front - &massive_[front_index_][0])) +
                   tmp
            << std::endl;
}

void deque::clear() {
  back_index_ = front_index_ = volume / 2;
  front_ = back_ = nullptr;
  std::cout << "ok" << std::endl;
}

int deque::exit() {
  std::cout << "bye";
  return 0;
}

void deque::expand_deque() {
  volume += massiveSize;
  int** tmp = new int* [volume] { NULL };
  for (int i = massiveSize / 2; i < volume - massiveSize / 2; i++) {
    tmp[i] = massive_[i - massiveSize / 2];
  }
  delete[] massive_;
  massive_ = tmp;
}

int main() {
  deque deq;
  std::string str;
  int number = 0, res = 1;
  while (res) {
    (std::cin >> str).get();
    if (str == "push_front") {
      (std::cin >> number).get();
      deq.push_front(number);
    } else if (str == "push_back") {
      (std::cin >> number).get();
      deq.push_back(number);
    } else if (str == "pop_front") {
      deq.pop_front();
    } else if (str == "pop_back") {
      deq.pop_back();
    } else if (str == "front") {
      deq.front();
    } else if (str == "back") {
      deq.back();
    } else if (str == "size") {
      deq.size();
    } else if (str == "clear") {
      deq.clear();
    } else if (str == "exit") {
      res = deq.exit();
    }
  }
  return 0;
}