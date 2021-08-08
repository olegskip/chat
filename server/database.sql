-- MariaDB dump 10.19  Distrib 10.6.3-MariaDB, for debian-linux-gnu (aarch64)
--
-- Host: localhost    Database: chat
-- ------------------------------------------------------
-- Server version	10.6.3-MariaDB-1:10.6.3+maria~focal

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `accounts`
--

DROP TABLE IF EXISTS `accounts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `accounts` (
  `username` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `password` char(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `accounts`
--

LOCK TABLES `accounts` WRITE;
/*!40000 ALTER TABLE `accounts` DISABLE KEYS */;
INSERT INTO `accounts` VALUES ('admin','5a38afb1a18d408e6cd367f9db91e2ab9bce834cdad3da24183cc174956c20ce35dd39c2bd36aae907111ae3d6ada353f7697a5f1a8fc567aae9e4ca41a9d19d'),('skip','aec90480a2232940cbb327dccea75b3f45a4033d1252f715273c4d88e359a1879bf276e95e143fbf43738501b62e33197cfe111d63c9c1af2db01e4503413696');
/*!40000 ALTER TABLE `accounts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `global_messages`
--

DROP TABLE IF EXISTS `global_messages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `global_messages` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `sender_username` varchar(30) NOT NULL,
  `text` varchar(500) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=102 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `global_messages`
--

LOCK TABLES `global_messages` WRITE;
/*!40000 ALTER TABLE `global_messages` DISABLE KEYS */;
INSERT INTO `global_messages` VALUES (1,'2021-08-08 14:32:33','admin','message {1}'),(2,'2021-08-08 14:32:33','admin','message {2}'),(3,'2021-08-08 14:32:33','admin','message {3}'),(4,'2021-08-08 14:32:33','admin','message {4}'),(5,'2021-08-08 14:32:33','admin','message {5}'),(6,'2021-08-08 14:32:33','admin','message {6}'),(7,'2021-08-08 14:32:33','admin','message {7}'),(8,'2021-08-08 14:32:33','admin','message {8}'),(9,'2021-08-08 14:32:33','admin','message {9}'),(10,'2021-08-08 14:32:33','admin','message {10}'),(11,'2021-08-08 14:32:33','admin','message {11}'),(12,'2021-08-08 14:32:33','admin','message {12}'),(13,'2021-08-08 14:32:33','admin','message {13}'),(14,'2021-08-08 14:32:33','admin','message {14}'),(15,'2021-08-08 14:32:33','admin','message {15}'),(16,'2021-08-08 14:32:33','admin','message {16}'),(17,'2021-08-08 14:32:33','admin','message {17}'),(18,'2021-08-08 14:32:33','admin','message {18}'),(19,'2021-08-08 14:32:33','admin','message {19}'),(20,'2021-08-08 14:32:33','admin','message {20}'),(21,'2021-08-08 14:32:33','admin','message {21}'),(22,'2021-08-08 14:32:33','admin','message {22}'),(23,'2021-08-08 14:32:34','admin','message {23}'),(24,'2021-08-08 14:32:34','admin','message {24}'),(25,'2021-08-08 14:32:34','admin','message {25}'),(26,'2021-08-08 14:32:34','admin','message {26}'),(27,'2021-08-08 14:32:34','admin','message {27}'),(28,'2021-08-08 14:32:34','admin','message {28}'),(29,'2021-08-08 14:32:34','admin','message {29}'),(30,'2021-08-08 14:32:34','admin','message {30}'),(31,'2021-08-08 14:32:34','admin','message {31}'),(32,'2021-08-08 14:32:34','admin','message {32}'),(33,'2021-08-08 14:32:34','admin','message {33}'),(34,'2021-08-08 14:32:34','admin','message {34}'),(35,'2021-08-08 14:32:34','admin','message {35}'),(36,'2021-08-08 14:32:34','admin','message {36}'),(37,'2021-08-08 14:32:34','admin','message {37}'),(38,'2021-08-08 14:32:34','admin','message {38}'),(39,'2021-08-08 14:32:34','admin','message {39}'),(40,'2021-08-08 14:32:34','admin','message {40}'),(41,'2021-08-08 14:32:34','admin','message {41}'),(42,'2021-08-08 14:32:34','admin','message {42}'),(43,'2021-08-08 14:32:34','admin','message {43}'),(44,'2021-08-08 14:32:34','admin','message {44}'),(45,'2021-08-08 14:32:34','admin','message {45}'),(46,'2021-08-08 14:32:34','admin','message {46}'),(47,'2021-08-08 14:32:34','admin','message {47}'),(48,'2021-08-08 14:32:34','admin','message {48}'),(49,'2021-08-08 14:32:34','admin','message {49}'),(50,'2021-08-08 14:32:34','admin','message {50}'),(51,'2021-08-08 14:32:34','admin','message {51}'),(52,'2021-08-08 14:32:34','admin','message {52}'),(53,'2021-08-08 14:32:34','admin','message {53}'),(54,'2021-08-08 14:32:34','admin','message {54}'),(55,'2021-08-08 14:32:34','admin','message {55}'),(56,'2021-08-08 14:32:34','admin','message {56}'),(57,'2021-08-08 14:32:34','admin','message {57}'),(58,'2021-08-08 14:32:34','admin','message {58}'),(59,'2021-08-08 14:32:34','admin','message {59}'),(60,'2021-08-08 14:32:34','admin','message {60}'),(61,'2021-08-08 14:32:34','admin','message {61}'),(62,'2021-08-08 14:32:35','admin','message {62}'),(63,'2021-08-08 14:32:35','admin','message {63}'),(64,'2021-08-08 14:32:35','admin','message {64}'),(65,'2021-08-08 14:32:35','admin','message {65}'),(66,'2021-08-08 14:32:35','admin','message {66}'),(67,'2021-08-08 14:32:35','admin','message {67}'),(68,'2021-08-08 14:32:35','admin','message {68}'),(69,'2021-08-08 14:32:35','admin','message {69}'),(70,'2021-08-08 14:32:35','admin','message {70}'),(71,'2021-08-08 14:32:35','admin','message {71}'),(72,'2021-08-08 14:32:35','admin','message {72}'),(73,'2021-08-08 14:32:35','admin','message {73}'),(74,'2021-08-08 14:32:35','admin','message {74}'),(75,'2021-08-08 14:32:35','admin','message {75}'),(76,'2021-08-08 14:32:35','admin','message {76}'),(77,'2021-08-08 14:32:35','admin','message {77}'),(78,'2021-08-08 14:32:35','admin','message {78}'),(79,'2021-08-08 14:32:35','admin','message {79}'),(80,'2021-08-08 14:32:35','admin','message {80}'),(81,'2021-08-08 14:32:35','admin','message {81}'),(82,'2021-08-08 14:32:35','admin','message {82}'),(83,'2021-08-08 14:32:35','admin','message {83}'),(84,'2021-08-08 14:32:35','admin','message {84}'),(85,'2021-08-08 14:32:35','admin','message {85}'),(86,'2021-08-08 14:32:35','admin','message {86}'),(87,'2021-08-08 14:32:35','admin','message {87}'),(88,'2021-08-08 14:32:35','admin','message {88}'),(89,'2021-08-08 14:32:35','admin','message {89}'),(90,'2021-08-08 14:32:35','admin','message {90}'),(91,'2021-08-08 14:32:35','admin','message {91}'),(92,'2021-08-08 14:32:35','admin','message {92}'),(93,'2021-08-08 14:32:35','admin','message {93}'),(94,'2021-08-08 14:32:35','admin','message {94}'),(95,'2021-08-08 14:32:35','admin','message {95}'),(96,'2021-08-08 14:32:35','admin','message {96}'),(97,'2021-08-08 14:32:35','admin','message {97}'),(98,'2021-08-08 14:32:35','admin','message {98}'),(99,'2021-08-08 14:32:35','admin','message {99}'),(100,'2021-08-08 14:32:35','admin','message {100}'),(101,'2021-08-08 14:42:42','admin','Message 101');
/*!40000 ALTER TABLE `global_messages` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-08-08 18:00:57
