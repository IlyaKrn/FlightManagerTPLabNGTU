package com.flightmanager.identityservice.repo;

import com.flightmanager.identityservice.config.PropertiesConfig;
import com.flightmanager.identityservice.exception.*;
import com.flightmanager.identityservice.models.UserModel;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Repository;
import org.springframework.web.client.RestTemplate;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@Repository
public class UserRepo {
    @Autowired
    private RestTemplate restTemplate;
    @Autowired
    private PropertiesConfig properties;

    public List<UserModel> getAll() throws HTTPException {
        String url = properties.getDatabaseServiceUrl() + properties.getUserGet();
        ResponseEntity<UserModel[]> r = restTemplate.getForEntity(url, UserModel[].class);
        if (r.getStatusCode().is2xxSuccessful())
            return r.getBody() == null ? null : new ArrayList<>(Arrays.asList(r.getBody()));
        if (r.getStatusCode().value() == 400)
            throw new HTTP400Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 401)
            throw new HTTP401Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 403)
            throw new HTTP403Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 401)
            throw new HTTP500Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        throw new HTTP500Exception("GET '" + url + "' return unchecked code" + r.getStatusCode().value());
    }

    public List<UserModel> getById(long id) throws HTTPException {
        String url = properties.getDatabaseServiceUrl() + properties.getUserGet() + "/?id=" + id;
        ResponseEntity<UserModel[]> r = restTemplate.getForEntity(url, UserModel[].class);
        if (r.getStatusCode().is2xxSuccessful())
            return r.getBody() == null ? null : new ArrayList<>(Arrays.asList(r.getBody()));
        if (r.getStatusCode().value() == 400)
            throw new HTTP400Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 401)
            throw new HTTP401Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 403)
            throw new HTTP403Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 401)
            throw new HTTP500Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        throw new HTTP500Exception("GET '" + url + "' return unchecked code" + r.getStatusCode().value());
    }

    public List<UserModel> getByEmail(String email) throws HTTPException {
        String url = properties.getDatabaseServiceUrl() + properties.getUserGet() + "/?email=" + email;
        ResponseEntity<UserModel[]> r = restTemplate.getForEntity(url, UserModel[].class);
        if (r.getStatusCode().is2xxSuccessful())
            return r.getBody() == null ? null : new ArrayList<>(Arrays.asList(r.getBody()));
        if (r.getStatusCode().value() == 400)
            throw new HTTP400Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 401)
            throw new HTTP401Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 403)
            throw new HTTP403Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 401)
            throw new HTTP500Exception("GET '" + url + "' return code" + r.getStatusCode().value());
        throw new HTTP500Exception("GET '" + url + "' return unchecked code" + r.getStatusCode().value());
    }

    public UserModel create(UserModel data) throws HTTPException {
        String url = properties.getDatabaseServiceUrl() + properties.getUserCreate();
        ResponseEntity<UserModel> r = restTemplate.postForEntity(url, data, UserModel.class);
        if (r.getStatusCode().is2xxSuccessful())
            return r.getBody();
        if (r.getStatusCode().value() == 400)
            throw new HTTP400Exception("POST '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 401)
            throw new HTTP401Exception("POST '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 403)
            throw new HTTP403Exception("POST '" + url + "' return code" + r.getStatusCode().value());
        if (r.getStatusCode().value() == 401)
            throw new HTTP500Exception("POST '" + url + "' return code" + r.getStatusCode().value());
        throw new HTTP500Exception("POST '" + url + "' return unchecked code" + r.getStatusCode().value());
    }
}
