package com.flightmanager.identityservice.repo;

import com.flightmanager.identityservice.models.UserModel;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import org.springframework.web.client.RestTemplate;

@Repository
public class UserRepo {
    @Autowired
    private RestTemplate restTemplate;

    public UserModel getById(long id) {

    }

    public UserModel getById(long id) {

    }
}
