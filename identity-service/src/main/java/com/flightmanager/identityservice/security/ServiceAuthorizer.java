package com.flightmanager.identityservice.security;

import com.flightmanager.identityservice.config.PropertiesConfig;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ServiceAuthorizer {

    @Autowired
    private PropertiesConfig properties;

    public boolean authorize(String token) {
        return token.equals(properties.getServiceToken());
    }
}
