package com.flightmanager.databaseservice.config;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;

@Configuration
public class PropertiesConfig {
    @Value("${security.service-token}")
    private String serviceToken;

}
