package com.ilyakrn.gateway.config;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;

@Getter
@Configuration
public class PropertiesConfig {
    private Logger log = LogManager.getLogger(PropertiesConfig.class);

    @Value("${security.service-token}")
    private String serviceToken;
    @Value("${security.service-token.header}")
    private String serviceTokenHeader;
}
