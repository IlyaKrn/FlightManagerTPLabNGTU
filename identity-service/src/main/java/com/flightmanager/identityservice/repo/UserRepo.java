package com.flightmanager.identityservice.repo;

import com.flightmanager.identityservice.models.UserModel;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import org.springframework.web.client.RestTemplate;

import java.util.List;

@Repository
public class UserRepo {
    @Autowired
    private RestTemplate restTemplate;

    public List<UserModel> getAll() {
        return null;
    }

    public UserModel getById(long id) {
        return null;
    }

    public UserModel getByEmail(String email) {
        return null;
    }

    public UserModel create(UserModel data) {
        return null;
    }
}
