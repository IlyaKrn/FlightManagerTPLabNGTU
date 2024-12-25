package com.flightmanager.identityservice.config;

import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;

@Getter
@Configuration
public class PropertiesConfig {
    @Value("${security.service-token}")
    private String serviceToken;
    @Value("${security.service-token.header}")
    private String serviceTokenHeader;

    @Value("${jwt.signing.key}")
    private String jwtSecret;


    @Value("${mapping.dispatcher.get}")
    private String userGet;
    @Value("${mapping.dispatcher.create}")
    private String userCreate;

    @Value("${url.database-service}")
    private String databaseServiceUrl;
}
