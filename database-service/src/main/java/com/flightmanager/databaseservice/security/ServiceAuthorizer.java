package com.flightmanager.databaseservice.security;

import com.flightmanager.databaseservice.config.PropertiesConfig;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
@Slf4j
@Service
public class ServiceAuthorizer {


    @Autowired
    private PropertiesConfig properties;

    public boolean authorize(String token) {
        log.debug("Received token: {}", token);
        log.debug("Expected service token: {}", properties.getServiceToken());

        boolean isAuthorized = token.equals(properties.getServiceToken());
        log.info("Authorization result: {}", isAuthorized ? "SUCCESS" : "FAILURE");

        return isAuthorized;
    }
}

