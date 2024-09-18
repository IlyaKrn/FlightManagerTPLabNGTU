package com.flightmanager.identityservice.service;

import com.flightmanager.identityservice.models.UserModel;
import com.flightmanager.identityservice.repo.UserRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class UserService {

    @Autowired
    private UserRepo userRepo;

    public List<UserModel> getAll() {
        return userRepo.getAll();
    }

    public UserModel getById(long id) {
        return userRepo.getById(id);
    }

    public UserModel getByEmail(String email) {
        return userRepo.getByEmail(email);
    }

    public UserModel create(UserModel data) {
        return userRepo.create(data);
    }

}
