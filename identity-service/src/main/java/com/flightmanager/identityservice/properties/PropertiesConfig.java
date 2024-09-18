package com.flightmanager.identityservice.properties;

import org.springframework.beans.factory.annotation.Configurable;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;

@Configuration
public class PropertiesConfig {


    @Value("${jwt.signing.key}")
    private String jwtSecret;
}
