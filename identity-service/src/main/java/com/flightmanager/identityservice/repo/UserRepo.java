package com.flightmanager.identityservice.repo;

import com.flightmanager.identityservice.config.PropertiesConfig;
import com.flightmanager.identityservice.exception.HTTPException;
import com.flightmanager.identityservice.models.UserModel;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import org.springframework.web.client.RestTemplate;

import java.util.ArrayList;
import java.util.List;

@Repository
public class UserRepo {
    @Autowired
    private RestTemplate restTemplate;
    @Autowired
    private PropertiesConfig properties;

    public List<UserModel> getAll() throws HTTPException {
        return (ArrayList<UserModel>) restTemplate.getForObject(properties.getDatabaseServiceUrl() + properties.getUserGet(), ArrayList.class);
    }

    public UserModel getById(long id) throws HTTPException {
        return restTemplate.getForObject(properties.getDatabaseServiceUrl() + properties.getUserGet() + "/" + id, UserModel.class);
    }

    public UserModel getByEmail(String email) throws HTTPException {
        return restTemplate.getForObject(properties.getDatabaseServiceUrl() + properties.getUserGet() + "/" + email, UserModel.class);
    }

    public UserModel create(UserModel data) throws HTTPException {
        return restTemplate.postForObject(properties.getDatabaseServiceUrl() + properties.getUserCreate(), data, UserModel.class);
    }
}
