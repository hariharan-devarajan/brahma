//
// Created by haridev on 8/28/22.
//
#include <brahma/interface/interface.h>
#include <brahma/singleton.h>

brahma::Interface::Interface() : bindings(), num_bindings(0) {
  utility = brahma::Singleton<brahma::InterfaceUtility>::get_instance();
}

int brahma::Interface::unbind() { return 0; }